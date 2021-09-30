
/*
 ported from msr-tools used in userland: https://github.com/intel/msr-tools.git
*/

#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <inttypes.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>

#include "msr.h"

#define DEBUG 0

#if DEBUG
	#define dbg_info(...) printf(__VA_ARGS__)
#else
	#define dbg_info(...)
#endif

uint64_t rdmsr_on_cpu(uint32_t reg, int cpu)
{
	uint64_t data;
	int fd;
	char msr_file_name[64];

	sprintf(msr_file_name, "/dev/cpu/%d/msr", cpu);
	fd = open(msr_file_name, O_RDONLY);
	if (fd < 0) {
		if (errno == ENXIO) {
			fprintf(stderr, "rdmsr: No CPU %d, in %s\n", cpu, msr_file_name);
			exit(2);
		} else if (errno == EIO) {
			fprintf(stderr, "rdmsr: CPU %d doesn't support MSRs, in %s\n", cpu, msr_file_name);
			exit(3);
		} else {
			perror("rdmsr: open");
			exit(127);
		}
	}

	if (pread(fd, &data, sizeof(data), reg) != sizeof(data)) {
		if (errno == EIO) {
			fprintf(stderr, "rdmsr: CPU %d cannot read MSR 0x%08"PRIx32"\n",
				cpu, reg);
			exit(4);
		} else {
			perror("rdmsr: pread");
			exit(127);
		}
	}

	close(fd);

	dbg_info("rdmsr: 0x%x, val: 0x%lx\n", reg, data);

	return data;
}


/* filter out ".", "..", "microcode" in /dev/cpu */
static int dir_filter(const struct dirent *dirp)
{
	if (isdigit(dirp->d_name[0]))
		return 1;
	else
		return 0;
}

void rdmsr_on_all_cpus(uint32_t reg)
{
	struct dirent **namelist;
	int dir_entries;

	dir_entries = scandir("/dev/cpu", &namelist, dir_filter, 0);
	while (dir_entries--) {
		rdmsr_on_cpu(reg, atoi(namelist[dir_entries]->d_name));
		free(namelist[dir_entries]);
	}
	free(namelist);
}

void wrmsr_on_cpu(uint32_t reg, int cpu, uint64_t regval)
{
	int fd;
	char msr_file_name[64];

	sprintf(msr_file_name, "/dev/cpu/%d/msr", cpu);
	fd = open(msr_file_name, O_WRONLY);
	if (fd < 0) {
		if (errno == ENXIO) {
			fprintf(stderr, "wrmsr: No CPU %d, in %s\n", cpu, msr_file_name);
			exit(2);
		} else if (errno == EIO) {
			fprintf(stderr, "wrmsr: CPU %d doesn't support MSRs, in %s\n",  cpu, msr_file_name);
			exit(3);
		} else {
			perror("wrmsr: open");
			exit(127);
		}
	}

	if (pwrite(fd, &regval, sizeof(regval), reg) != sizeof(regval)) {
		if (errno == EIO) {
			fprintf(stderr,
				"wrmsr: CPU %d cannot set MSR "
				"0x%08"PRIx32" to 0x%016"PRIx64"\n",
				cpu, reg, regval);
			exit(4);
		} else {
			perror("wrmsr: pwrite");
			exit(127);
		}
	}

	close(fd);

	dbg_info("wrmsr: 0x%x, val: 0x%lx\n", reg, regval);

	return;
}


void wrmsr_on_all_cpus(uint32_t reg, uint64_t regval)
{
	struct dirent **namelist;
	int dir_entries;

	dir_entries = scandir("/dev/cpu", &namelist, dir_filter, 0);
	while (dir_entries--) {
		wrmsr_on_cpu(reg, atoi(namelist[dir_entries]->d_name), regval);
		free(namelist[dir_entries]);
	}
	free(namelist);
}
