#!/usr/bin/python
# example usage: ./extract_table.py ./3dio_jbl/ L

import sys
import numpy as np
import pandas as pd

np.set_printoptions(precision=2)

print("Args Count: ",len(sys.argv))
print("Args List: ",str(sys.argv))

if(len(sys.argv) < 2):
    sys.exit()

dirInput = str(sys.argv[1])
chInput = str(sys.argv[2])

print("Input Directory: %s" % dirInput)
print("Channel: %s" % chInput)

if chInput!='L':
    pass
elif chInput!='R':
    pass
else:
    sys.exit()

arrScale = np.array([1,2,3,4,5,6,7,8,9,10,11])

def get_freq(freq_name,freq_val,dir_input,ch_input):
    df = pd.read_csv('%s/%sHz-%s.csv' % (dir_input,freq_name,ch_input))
    arr = df.loc[:,'%s-%s' % (freq_val,ch_input)].to_numpy()
    val = np.array([
        (arr[0] + arr[1] + arr[2])/3, # 11
        (arr[3] + arr[4] + arr[5])/3, # 10
        (arr[6] + arr[7] + arr[8])/3, # 9
        (arr[9] + arr[10] + arr[11])/3, # 8
        (arr[12] + arr[13] + arr[14])/3, # 7
        (arr[15] + arr[16] + arr[17])/3, # 6
        (arr[18] + arr[19] + arr[20])/3, # 5
        (arr[21] + arr[22] + arr[23])/3, # 4
        (arr[24] + arr[25] + arr[26])/3, # 3
        (arr[27] + arr[28] + arr[29])/3, # 2
        (arr[30] + arr[31] + arr[32])/3, # 1
        ])

    return val

val_125 = get_freq('125', '125', dirInput, chInput)
val_250 = get_freq('250', '125', dirInput, chInput)



