#Instructions (Fixed 0)
wrmsr -p 1 0x38f 0x7000000ff
wrmsr -p 1 0x38d 0xb

#frontend
#IDQ_UOPS_NOT_DELIVERED.CORE
wrmsr -p 1 0x186 0x43019c

#backend
#EXE_ACTIVITY.EXE_BOUND_0_PORTS
wrmsr -p 1 0x187 0x4301a6
#EXE_ACTIVITY.1_PORTS_UTIL
wrmsr -p 1 0x188 0x4302a6
#Few_Uops_Executed_Threshold(self, EV, level))
#
#CYCLE_ACTIVITY.STALLS_MEM_ANY
wrmsr -p 1 0x189 0x144314a3
#EXE_ACTIVITY.BOUND_ON_STORES
wrmsr -p 1 0x18a 0x4340a6

# CYCLE_ACTIVITY.STALLS_TOTAL
wrmsr -p 1 0x18b 0x44304a3

# RESOURCE_STALLS.ANY
wrmsr -p 1 0x18c 0x4301a2
