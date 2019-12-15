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
H_RATIO = (250-62)/(H_MAX-H_MIN) # heigh per step
D_MAX = 215
D_MIN = 0
D_RATIO = 1 # 1mm
#Formating
TX_FMT = 'LL'
RX_FMT = 'LLL' # l: signed long, L: unsigned long, f float
RX_L = struct.calcsize(RX_FMT)

def calculate(r,h,d,downangle = 0):
    d = (d-214)
    dd = d*D_RATIO
    rr = r*R_RATIO
    x = dd*math.cos(rr)
    y = dd*math.sin(rr)
    z = h*H_RATIO-(dd*math.sin(downangle/150*math.pi))
    return x,y,z
def condition(r,h,d):
    return d>D_MIN
def pattern():
    for th in range(H_MIN,H_MAX,H_STEP):
        for tr in range(R_MIN,R_MAX,R_STEP):
            yield th,tr
def main():
    r = b''
    with serial.Serial("COM5",115200,timeout=1) as s:
        print(".")
        p = pattern()
        for th,tr in p:
            s.write(struct.pack  (TX_FMT,tr,th))
            while len(r)<RX_L:
                r += s.read(RX_L)
            print(r)
            (rr,rh,rd) = struct.unpack(RX_FMT,r[:RX_L])
            r = r[RX_L:]
            if condition(rr,rh,rd):
                break
            else:
                yield calculate(rr,rh,rd)
def point_from_file(f = "2nd test scan log.txt"):
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
if __name__ == "__main__":
    with open("tmp.asc","w") as f:
        for i in point_from_file():
            #print(i)
            if len(i)==3:
                f.write("%.6f %.6f %.6f\r\n" % i)
    from pc2stl import pc2stl
    pc2stl("tmp.asc")
    #cleanup
    #os.remove("tmp.asc")
    
    
