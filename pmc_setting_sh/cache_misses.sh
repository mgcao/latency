#!/bin/bash

#this setting default for intel core CPUs

#Instructions (Fixed 0)
#wrmsr -p 1 0x38d 0xb

rt_cpu=3

#Instructions (Fixed 0/1/2)
wrmsr -p $rt_cpu 0x38d 0xbbb

# L2_RQSTS.MISS
wrmsr -p $rt_cpu 0x186 0x433f24

# L3_LAT_CACHE.MISS
wrmsr -p $rt_cpu 0x187 0x43412e

#CYCLE_ACTIVITY.CYCLES_L2_MISS
wrmsr -p $rt_cpu 0x188 0x14301a3

# CYCLE_ACTIVITY.STALLS_L2_MISS
wrmsr -p $rt_cpu 0x189 0x54305a3

#CYCLE_ACTIVITY.CYCLES_L3_MISS
wrmsr -p $rt_cpu 0x18a 0x24302a3

#CYCLE_ACTIVITY.STALLS-total
wrmsr -p $rt_cpu 0x18b 0x44304a3

#CYCLE_ACTIVITY.CYCLES_L1D_MISS
wrmsr -p $rt_cpu 0x18c 0x84308a3

#CYCLE_ACTIVITY.STALLS_L1D_MISS
wrmsr -p $rt_cpu 0x18d 0x0c430ca3


#CYCLE_ACTIVITY.CYCLES_MEM_ANY
#wrmsr -p 1 0x18c 0x104310a3

# CYCLE_ACTIVITY.STALLS_MEM_ANY 
#wrmsr -p 1 0x18d 0x144314a3

#echo -e "\t\t\t\t  total-Inst  L2-Miss      L3-Miss      Cycles-L2    Cycles-L3    Cycles-Mem   Stalls-L2    Stalls-L3    Stalls-Mem"
#echo -e "Latency   \tTimes  \tInst  \tL2-Miss  \tL3-Miss   \tCycles-L2   \tStalls-L2  \tCycles-L3  \tStalls-L3  \tCycles-Mem  \tStalls-Mem"

echo -e "Latency Times Inst Cycles Tsc L2-Miss L3-Miss Cycles-L2 Stalls-L2 Cycles-L3 Stalls-L3 Cycles-L1 Stalls-L1"
