#Instructions
wrmsr -p 1 0x38d 0x3

############# PMC0 ################
# L2_RQSTS.MISS
wrmsr -p 1 0x186 0x433f24

############# PMC1 ################
# L2_RQSTS.PF_MISS
wrmsr -p 1 0x187 0x433824

############# PMC2 ################
# L2_RQSTS.ALL_DEMAND_MISS
wrmsr -p 1 0x188 0x432724


############# PMC3 ################
# L2_RQSTS.CODE_RD_MISS
wrmsr -p 1 0x189 0x432424

############# PMC4 ################
# L2_RQSTS.DEMAND_DATA_RD_MISS
wrmsr -p 1 0x18a 0x432124

############# PMC5 ################
wrmsr -p 1 0x18b 0

############# PMC6 ################
# CYCLE_ACTIVITY.STALLS_L2_MISS
wrmsr -p 1 0x18c 0x54305a3

############# PMC7 ################
# CYCLE_ACTIVITY.STALLS_MEM_ANY
wrmsr -p 1 0x18d 0x54310a3