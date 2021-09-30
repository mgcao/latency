/*
 *
 * (C) 2021      Minggui Cao <minggui.cao@intel.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License Version
 * 2 as published by the Free Software Foundation.
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stddef.h>
#include <string.h>
#include <cpuid.h>

#include "msr.h"
#include "pmc.h"

//#define PMC_MAX 8
#define PMC_MAX 8  //EHL just 4 general counters

#define TYPE_FIXED_CTR0  		(1ULL << 30)
#define TYPE_FIXED_CTR1  		((1ULL << 30) | 1)
#define TYPE_FIXED_CTR2  		((1ULL << 30) | 2)

#define PERF_GLOBAL_CTRL		0x38f /* Global CTRL MSR */

static uint8_t  g_counters = 0;
static uint64_t g_pmc_mask = 0x700000000; //7 is for 3 fixed pmc

static uint64_t g_start[PMC_MAX];
static uint64_t g_stop[PMC_MAX];
static uint64_t g_delta[PMC_MAX];

static uint64_t pmc_inst_start;  //total inst
static uint64_t pmc_inst_stop;
static uint64_t pmc_cycles_start; //total core cycles
static uint64_t pmc_cycles_stop;
static uint64_t pmc_tsc_start;  //total cycles/tsc based
static uint64_t pmc_tsc_stop;

static inline uint64_t native_rdpmc(uint32_t idx)
{
    uint32_t lo, hi;

    __asm__ volatile("rdpmc" : "=a" (lo), "=d" (hi) : "c" (idx));

    return ((uint64_t)lo) | (((uint64_t)hi) << 32);
}

void pmc_pre_read(void)
{
	int cnt;

	pmc_inst_start = native_rdpmc(TYPE_FIXED_CTR0);
	pmc_cycles_start = native_rdpmc(TYPE_FIXED_CTR1);
	pmc_tsc_start = native_rdpmc(TYPE_FIXED_CTR2);

	for( cnt = 0; cnt < g_counters; cnt++) {
		g_start[cnt] = native_rdpmc(cnt);
	}
}

void pmc_post_read(void)
{
	int cnt;

	pmc_inst_stop = native_rdpmc(TYPE_FIXED_CTR0);
	pmc_cycles_stop = native_rdpmc(TYPE_FIXED_CTR1);
	pmc_tsc_stop = native_rdpmc(TYPE_FIXED_CTR2);

	for( cnt = 0; cnt < g_counters; cnt++) {
		g_stop[cnt] = native_rdpmc(cnt);
	}

    for( cnt = 0; cnt < g_counters; cnt++) {
        g_delta[cnt] = g_stop[cnt] - g_start[cnt];
    }

}

int pmc_dump_delta_info(char *buf, uint32_t times, uint32_t latency)
{
	int size = 0;

	size = sprintf(buf, "\n%u\t%u\t%lu\t%lu\t%lu", latency, times, pmc_inst_stop - pmc_inst_start,
		pmc_cycles_stop - pmc_cycles_start, pmc_tsc_stop - pmc_tsc_start);

	for (int i = 0; i < g_counters; i++) {
		size += sprintf(buf + size, "\t%lu", g_delta[i]);
	}

	return size;
}

void pmc_start_counting(int cpu)
{
	wrmsr_on_cpu(PERF_GLOBAL_CTRL, cpu, g_pmc_mask); //start 3 fixed and 4/6/8 general counter
}

void pmc_stop_counting(int cpu)
{
	wrmsr_on_cpu(PERF_GLOBAL_CTRL, cpu, 0); //stop all counter
}

#define RDPMC_PATH "/sys/devices/cpu/rdpmc"

bool pmc_init(void)
{
    //emable rdpmc in userland
	int ret = system("echo 2 > " RDPMC_PATH);

	//printf("pmc_init system ret=%d\n", ret);
	if (ret != 0) {
		fprintf(stderr, RDPMC_PATH " set failed, please check! need expose it from kernel!\n");
		return false;
	}

    //use cpuid to check its version: >=4
	unsigned int ebx = 0, ecx = 0, edx = 0, eax = 0;

	__get_cpuid(0xa, &eax, &ebx, &ecx, &edx);
	g_counters = (eax & 0xff00) >> 8;

	uint32_t masks = 0;
	for (uint8_t i = 0; i < g_counters; i++) {
		masks |= (1 << i);
	}

	g_pmc_mask |= masks;

	printf("pmu counters: %d, ctrl mask=0x%lx\n", g_counters, g_pmc_mask);

	return true;
}