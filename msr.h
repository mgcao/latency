#if !defined(__MSR_H__)
#define __MSR_H__

uint64_t rdmsr_on_cpu(uint32_t reg, int cpu);
void rdmsr_on_all_cpus(uint32_t reg);

void wrmsr_on_cpu(uint32_t reg, int cpu, uint64_t regval);
void wrmsr_on_all_cpus(uint32_t reg, uint64_t regval);

#endif