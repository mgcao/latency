#!/bin/bash

#this setting default for intel core CPUs

############# PMC0 ################
# MEM_LOAD_RETIRED.L2_HIT
wrmsr -p 1 0x186 0x4302d1

############# PMC1 ################
# MEM_LOAD_RETIRED.L2_MISS
wrmsr -p 1 0x187 0x4310d1

############# PMC2 ################
# MEM_LOAD_RETIRED.L3_HIT
wrmsr -p 1 0x188 0x4304d1

############# PMC3 ################
# MEM_LOAD_RETIRED.L3_MISS
wrmsr -p 1 0x189 0x4320d1

############# PMC4 ################
# L2_RQSTS.MISS
wrmsr -p 1 0x18a 0x433f24

############# PMC5 ################
# L3_LAT_CACHE.MISS
wrmsr -p 1 0x18B 0x43412e


############# PMC6  ################
# MEM_LOAD_RETIRED.L1_HIT
wrmsr -p 1 0x18c 0x4301d1

############# PMC7 ################
# MEM_LOAD_RETIRED.L1_MISS
wrmsr -p 1 0x18d 0x4308d1


############# PMC6 ################
#CYCLE_ACTIVITY.STALLS_MEM_ANY
#wrmsr -p 1 0x18c 0x144314a3

############# PMC7 ################
# CYCLE_ACTIVITY.STALLS_TOTAL
#wrmsr -p 1 0x18d 0x44304a3

#Instructions (Fixed 0)
#wrmsr -p 1 0x38f 0x7000000ff
wrmsr -p 1 0x38d 0xbbb

echo -e "Latency Times Inst Cycles Tsc Load-L2hit Load-L2miss Load-L3hit Load-L3miss L2-misses L3-misses Load-L1hit Load-L1miss\n"
