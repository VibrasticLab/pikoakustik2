#!/usr/bin/python
# example usage: ./extract_table.py 3dio_jbl L

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

def get_str(arr_freq,arr_freq_name):
    vStr = "%s & %.2f & %.2f & %.2f  & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.f" % (
        arr_freq_name,
        arr_freq[0],
        arr_freq[1],
        arr_freq[2],
        arr_freq[3],
        arr_freq[4],
        arr_freq[5],
        arr_freq[6],
        arr_freq[7],
        arr_freq[8],
        arr_freq[9],
        arr_freq[10]
        )

    return vStr

val_125 = get_freq('125', '119', dirInput, chInput)
val_250 = get_freq('250', '224', dirInput, chInput)
val_500 = get_freq('500', '459.5', dirInput, chInput)
val_1000 = get_freq('1000', '917.5', dirInput, chInput)
val_2000 = get_freq('2000', '1.83k', dirInput, chInput)
val_4000 = get_freq('4000', '3.76k', dirInput, chInput)
val_8000 = get_freq('8000', '7.72k', dirInput, chInput)

# latex table
str_tex = "freq/scale & 11 & 10 & 9 & 8 & 7 & 6 & 5 & 4 & 3 & 2 & 1 \\\\\n\
%s \\\\\n%s \\\\\n%s \\\\\n%s \\\\\n%s \\\\\n%s \\\\\n%s \\\\\n" % (
        get_str(val_125, '125Hz'),
        get_str(val_250, '250Hz'),
        get_str(val_500, '500Hz'),
        get_str(val_1000, '1000Hz'),
        get_str(val_2000, '2000Hz'),
        get_str(val_4000, '4000Hz'),
        get_str(val_8000, '8000Hz')
        )

print(str_tex)

tex_out = open('./%s-%s.tex' % (dirInput,chInput), "w")
tex_out.write(str(str_tex))
tex_out.close()

