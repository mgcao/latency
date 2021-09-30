#!/bin/bash

#Instructions (Fixed 0)
#wrmsr -p 1 0x38d 0xb

#Instructions (Fixed 0/1/2)
wrmsr -p 1 0x38d 0xbbb

# LONGEST_LAT_CACHE.REFERENCE
wrmsr -p 1 0x186 0x434F2E

# LONGEST_LAT_CACHE.MISS
wrmsr -p 1 0x187 0x43412e

# MEM_LOAD_UOPS_RETIRED.L2_HIT
wrmsr -p 1 0x188 0x4302d1

# MEM_LOAD_UOPS_RETIRED.L2_MISS
wrmsr -p 1 0x189 0x4310d1


echo -e "Latency Times Inst Cycles Tsc L3-REF L3-Miss L2_HIT L2_MISS"
