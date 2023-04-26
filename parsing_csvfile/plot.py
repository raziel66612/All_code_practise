# from matplotlib import *
import csv

# csv.reader()
filename = "sample1_test2_full extension_180mm.csv"
# filename= "sample1_test3_300mm.csv"

fields=[]
rows=[]
Mag=[]

## Trial 1 : works

# with open(filename,'r') as csvfile:
#     csvreader=csv.reader(csvfile)

#     fields = next(csvreader)

#     for row in csvreader:
#         rows.append(row)

#     print("Total no. of rows: %d"%(csvreader.line_num))

# print('Field names are: '+','.join(field for field in fields))
# print('\n')
### Print first 5 rows and all columns
# for row in rows[:5]: 
#     for col in row[:]:
#         print("%5s"%col,end=" "),
#     print('\n')
    
## Trial 2: Works
import numpy as np
import matplotlib.pyplot as plt

Area=6*3.175
L0=33 #gauge Length
max_extension=300

## Allocate values of Force and Torque components to array
Fx=np.array([])  ##Initializing numpy array
Fy=np.array([])
Fz=np.array([])
Tx=[]   ##Initializing python list
Ty=[]
Tz=[]
with open('sample1_test2_full extension_180mm.csv', 'rU') as data:
# with open('sample1_test3_300mm.csv', 'rU') as data:
    reader = csv.reader(data)
    row = list(reader)
    # for x in row[1:2]:
    #     for y in x:
    #         print (type(float(y)))
            
    for x in row[120:]:
        # Fx.append(x[0])
        Fx=np.append(Fx,float(x[0])) ##appending numpy array, x[0] is string when taken from csv file, so for type conversion we are using float() to convert string to float, for numerical operations
        Fy=np.append(Fy,float(x[1]))
        Fz=np.append(Fz,float(x[2]))
        Tx.append(x[3])      ##appending python list
        Ty.append(x[4])
        Tz.append(x[5])
        
        
        
F_res=np.sqrt(np.square(Fx)+np.square(Fy))  #resultant Force
S_res=F_res/Area  #resultant stress

max_stress=0.0
count=0
for i in range(len(S_res)):
    if max_stress < S_res[i]:
        max_stress=S_res[i]
        count=i

S_load=np.array([])
S_unload=np.array([])

# for i in range(len(Fx)-1):
#     if (Fx[i]<Fx[i+1]):
#         S_load=np.append(S_load,S_res[i])
#     elif Fx[i]>Fx[i+1]:
#         S_unload=np.append(S_unload,S_res[i])


# for i in range(len(S_res)-1):
#     if (Fx[i]<Fx[i+1]) and (i<=count):
#         S_load=np.append(S_load,S_res[i])
#     elif Fx[i]>Fx[i+1] and (i>=count) and (abs(Fx[i]-Fx[i+1])<0.5):
#         S_unload=np.append(S_unload,S_res[i])

for i in range(len(S_res)-25): ##adjust endpoints to eliminate
    if i<count:    ##here, adjust initial datapoints to eliminate
        S_load=np.append(S_load,S_res[i])
    elif i==count:
        S_load=np.append(S_load,S_res[i])
        S_unload=np.append(S_unload,S_res[i])
    elif i>=count and i>count+15:   ## here adjust endpoint to adjust at the end of loading curve
        S_unload=np.append(S_unload,S_res[i])


i_load=len(S_load)
disp=np.linspace(0,max_extension,i_load)
strain_load=disp/L0
plt.plot(strain_load,S_load) 

i_unload=len(S_unload)
disp=np.linspace(max_extension,0,i_unload)
strain_unload=disp/L0
plt.plot(strain_unload,S_unload)
# plt.plot(strain[:80],S_res[:80])
