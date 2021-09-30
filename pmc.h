#if !defined(__PMC_H__)
#define __PMC_H__

bool pmc_init(void);

void pmc_start_counting(int cpu);
void pmc_stop_counting(int cpu);

void pmc_pre_read(void);
void pmc_post_read(void);

int pmc_dump_delta_info(char *buf, uint32_t times, uint32_t latency);

#endif