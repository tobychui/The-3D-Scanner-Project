#import serial
import struct
import math
import os
#Constants
R_MAX = 200 #max rotation
R_MIN = 0
R_STEP = 1
R_RATIO = 2*math.pi /(R_MAX -R_MIN)# radian
H_MAX = 600
H_MIN = 0
H_STEP = 1
H_RATIO = (250 - 62)/(H_MAX-H_MIN) # heigh per step
D_MAX = 180
D_MIN = 0
D_RATIO = 1 # 1mm
#Formating
TX_FMT = 'LL'
RX_FMT = 'LLL' # l: signed long, L: unsigned long, f float
RX_L = struct.calcsize(RX_FMT)

def calculate(r,h,d,downangle = 0):
    d = (d-D_MAX)
    dd = d*D_RATIO
    rr = r*R_RATIO
    x = dd*math.cos(rr)
    y = dd*math.sin(rr)
    z = h*H_RATIO-(dd*math.sin(downangle/150*math.pi))
    return x,y,z

def point_from_file(f = "test5.txt"):
    with open(f,"r") as f:
        for _ in range(13):
            f.readline()
        for i in f:
            try:
                h,r,d = [int(j) for j in i.split()]
                if d>D_MAX or d<1:
                    continue
                yield calculate(r,h,d)
            except Exception as e:
                print(e)
                break
            
with open("tmp.asc","w") as f:
    for i in point_from_file():
        #print(i)
        if len(i)==3:
            f.write("%.6f %.6f %.6f\n" % i)
                
    
