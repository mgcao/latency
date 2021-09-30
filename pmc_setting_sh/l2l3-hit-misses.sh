#!/bin/bash

#this is for Intel core serial CPU

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
# L2_RQSTS.REF
wrmsr -p 1 0x18a 0x43ef24

############# PMC5 ################
# L2_RQSTS.MISS
wrmsr -p 1 0x18B 0x433f24

############# PMC6 ################
# L3_LAT_CACHE.REF
wrmsr -p 1 0x18C 0x434F2e

############# PMC7 ################
# L3_LAT_CACHE.MISS
wrmsr -p 1 0x18D 0x43412e

#Instructions (Fixed 0)
#wrmsr -p 1 0x38f 0x7000000ff
wrmsr -p 1 0x38d 0xbbb

echo -e "Latency Times Inst Cycles Tsc Mem.L2.Hit Mem.L2.Miss Mem.L3.Hit Mem.L3.Miss L2-REF L2-MISS L3-REF L3-MISS"
