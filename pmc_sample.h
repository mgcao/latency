#if !defined(__PMC_SAMPLE_H__)
#define __PMC_SAMPLE_H__

void init_extra_sampling(int target_cpu, uint32_t sample_count, uint32_t sample_interval, uint32_t time_check);
void pre_extra_sample(void);
void post_extra_sample(uint64_t latency, uint64_t cycles);
void output_extra_sample(void);

#endif