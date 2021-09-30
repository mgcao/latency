#!/bin/bash

# L2_RQSTS.REF
wrmsr -p 1 0x186 0x43ff24

# L2_RQSTS.MISS, CFL/Sky-L, Kaby-L (whl same)
wrmsr -p 1 0x187 0x433f24

# L3_LAT_CACHE.MISS
wrmsr -p 1 0x188 0x43412e

# OFFCORE_REQUESTS.ALL_REQUESTS 
wrmsr -p 1 0x189 0x4380b0

#OFFCORE_REQUESTS_OUTSTANDING.ALL_DATA_RD
wrmsr -p 1 0x18a 0x1430860

#OFFCORE_REQUESTS_OUTSTANDING.DEMAND_RFO
wrmsr -p 1 0x18b 0x1430460

#CYCLE_ACTIVITY.STALLS_L2_MISS
wrmsr -p 1 0x18c 0x54305a3

#CYCLE_ACTIVITY.STALLS_L3_MISS 
wrmsr -p 1 0x18d 0x64306a3

#CYCLE_ACTIVITY.STALLS_MEM_ANY
#wrmsr -p 1 0x189 0x144314a3

#Instructions (Fixed 0/1/2)
wrmsr -p 1 0x38d 0xbbb

echo -e "Latency Times Inst Cycles Tsc L2-Ref L2-Miss L3-Miss Offcore-All Offcore-allDataRD Offcore-RFO Stalls-L2 Stalls-L3"
