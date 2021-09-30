############# Fixed 0 ################
# Instructions
wrmsr -p 1 0x38d 0x3

############# PMC0 ################
# DTLB_LOAD_MISSES.STLB_HIT
wrmsr -p 1 0x186 0x432008

############# PMC1 ################
# MEM_INST_RETIRED.STLB_MISS_LOADS
wrmsr -p 1 0x187 0x4311d0

############# PMC2 ################
# DTLB_LOAD_MISSES.MISS_CAUSES_A_WALK
wrmsr -p 1 0x188 0x430108

############# PMC3 ################
# DTLB_LOAD_MISSES.WALK_COMPLETED_4K
wrmsr -p 1 0x189 0x430208

############# PMC4 ################
# DTLB_LOAD_MISSES.WALK_COMPLETED_2M_4M
wrmsr -p 1 0x18a 0x430408


############# PMC5 ################
wrmsr -p 1 0x18b 0

############# PMC6 ################
wrmsr -p 1 0x18c 0

############# PMC7 ################
# CYCLE_ACTIVITY.STALLS_L2_MISS
wrmsr -p 1 0x18d 0x54305a3
