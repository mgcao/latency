

# FETCH_STALL.ALL
wrmsr -p 1 0x186 0x430086

# L3_LAT_CACHE.MISS
wrmsr -p 1 0x187 0x43412e

# CYCLE_ACTIVITY.STALLS_L2_MISS
wrmsr -p 1 0x188 0x54305a3

#CYCLE_ACTIVITY.STALLS_L3_MISS 
wrmsr -p 1 0x189 0x64306a3

#CYCLE_ACTIVITY.STALLS_MEM_ANY
#wrmsr -p 1 0x18a 0x144314a3

# CYCLE_ACTIVITY.STALLS_TOTAL
#wrmsr -p 1 0x18b 0x44304a3

# RESOURCE_STALLS.ANY
#wrmsr -p 1 0x18c 0x4301a2

# RESOURCE_STALLS.SB
#wrmsr -p 1 0x18d 0x4308a2

#Instructions (Fixed 0)
#wrmsr -p 1 0x38f 0x7000000ff
wrmsr -p 1 0x38d 0xbbb

echo -e "Latency Times Inst Cycles Tsc L2-Miss L3-Miss Stalls-L2 Stalls-L3"

#Stalls-Mem Stalls-Total Stalls-Res Stalls-SB
