############# Fixed 0 ################
# Instructions
wrmsr -p 1 0x38d 0x3

############# PMC0 ################
# ITLB_LOAD_MISSES.STLB_HIT
wrmsr -p 1 0x186 0x432085

############# PMC1 ################
# MEM_INST_RETIRED.STLB_MISS_LOADS
wrmsr -p 1 0x187 0x4311d0

############# PMC2 ################
# ITLB_MISSES.MISS_CAUSES_A_WALK
wrmsr -p 1 0x188 0x430185

############# PMC3 ################
# ITLB_MISSES.WALK_COMPLETED
wrmsr -p 1 0x189 0x430E85

############# PMC4 ################
wrmsr -p 1 0x18a 0

############# PMC5 ################
wrmsr -p 1 0x18b 0

############# PMC6 ################
# HW_INTERRUPTS.RECEIVED
wrmsr -p 1 0x18c 0x4301cb

############# PMC7 ################
# STALL due to L2 miss
wrmsr -p 1 0x18d 0x54305a3