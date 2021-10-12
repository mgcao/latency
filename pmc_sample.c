#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <inttypes.h>

#include "msr.h"
#include "pmc.h"

#include "pmc_sample.h"

//add for extra info
//static bool ignore_extra_sample = true;
static bool has_pmc_info = false;

#define INFO_BUF_SIZE (128 * 1024U)
#define INFO_BUF_SIZE_LIMIT  (INFO_BUF_SIZE - 256)
static char extra_info_buf[INFO_BUF_SIZE];
static uint32_t	buf_offset = 0;

#define PMC_ON_CPU 1

#define MAX_CHECK_TIME  10000 // ns, 10us by default

static int default_pmc_cpu = PMC_ON_CPU;
static uint32_t max_time_check = MAX_CHECK_TIME;
static uint32_t random_sample_count = 0;
static uint32_t random_sample_interval = 1000; //unit ms
static uint64_t next_sample_cycle = 0;

//for extra info sampling
void init_extra_sampling(int target_cpu, uint32_t sample_count, uint32_t sample_interval, uint32_t time_check)
{
    default_pmc_cpu = target_cpu;
    random_sample_count = sample_count;
    random_sample_interval = sample_interval;
    max_time_check = time_check;

	//current set fixed cpu PMC_ON_CPU
	has_pmc_info = pmc_init();
	if (!has_pmc_info) {
		perror("PMU can't count!\n");
        return;
	}

	//start counter
	if (has_pmc_info) {	
		pmc_start_counting(default_pmc_cpu);
		printf("Post PMC build, note: need run PMC script first!\n");
	}

	buf_offset = 0;
	
	printf("random_sample_count: %d, interval: %d cycles, max-check: %dns\n", random_sample_count,
        random_sample_interval, max_time_check);
}

void pre_extra_sample(void)
{
	if (has_pmc_info) {
		pmc_pre_read();
	}
}

void post_extra_sample(uint64_t latency, uint64_t cycles)
{
	if (has_pmc_info) {
	
		pmc_post_read();

        //for debug
        //printf("next: %ld, cycles:%ld\n", next_sample_cycle, cycles);

		//for ramdom sample,  if random sample set, ingore min/max setting
		if ((random_sample_count > 0) && (next_sample_cycle == cycles) && (buf_offset < INFO_BUF_SIZE_LIMIT)) {

			int size = pmc_dump_delta_info(extra_info_buf + buf_offset, cycles, latency);
			buf_offset += size;
			next_sample_cycle += random_sample_interval;
	
		} else if ((latency > max_time_check) && (buf_offset < INFO_BUF_SIZE_LIMIT)) {

			int size = pmc_dump_delta_info(extra_info_buf + buf_offset, cycles, latency);
			buf_offset += size;
		} 
	}
}

void output_extra_sample(void)
{
	if (has_pmc_info) {	
		pmc_stop_counting(default_pmc_cpu);
	}

	if (buf_offset >= INFO_BUF_SIZE_LIMIT) {
		int size = sprintf(extra_info_buf + buf_offset, "\n!too much samples saved, buffer to overflow!!!\n");
		buf_offset += size;
	}

	if (buf_offset > 0) {
		fputs(extra_info_buf, stdout);
		fputs("\n", stdout);
	} else {
        fputs("no extra sampled data\n", stdout);
    }
}
