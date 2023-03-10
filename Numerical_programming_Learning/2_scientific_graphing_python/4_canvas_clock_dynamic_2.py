from tkinter import *
from math import *
from time import *

root = Tk()  
root.title("Canvas")



def Clock0(w,nx,ny):
    x0=nx/2; lx= (9/20)*nx 
    y0=nx/2; ly= (9/20)*ny
    r0 = 0.9*min(lx,ly)  #dist of hour labelf from center
    r1 = 0.6*min(lx,ly)  #length of hour hand
    r2 = 0.8*min(lx,ly)  #length of minute hand

    w.create_oval(x0-lx,y0-ly,x0+lx,y0+ly,width=2)
    for i in range(1,13):
        theta= pi/6 * i
        x = x0 + r0*sin(theta)
        y = y0 - r0*cos(theta)
        w.create_text(x,y,text=str(i))     # labels of clock hour ranging from 1 to 12 
    
    t=localtime()  #current time [year,month,day,hour,min,second,weekday,something,something]
    t_sec=t[5]    #seconds of current time
    t_min=t[4] + t_sec/60
    t_hr=t[3]%12 + t_min/60 

    theta = pi/6 * t_hr
    x = x0 + r1*sin(theta)
    y = y0 - r1*cos(theta)
    w.create_line(x0,y0,x,y,arrow=LAST, fill="black", width = 4)

    theta = pi/(6*5) * t_min
    x = x0 + r2*sin(theta)
    y = y0 - r2*cos(theta)
    w.create_line(x0,y0,x,y,arrow=LAST, fill="blue", width = 2)

    theta = pi/(6*5) * t_sec
    x = x0 + r2*sin(theta)
    y = y0 - r2*cos(theta)
    w.create_line(x0,y0,x,y,arrow=LAST, fill="red", width = 1.5)

def Clock(w,nx,ny):
    w.delete(ALL)
    Clock0(w,nx,ny)
    w.after(1,Clock,w,nx,ny)

Nx=300
Ny=300   #canvas size
a=Canvas(root, width=Nx,height=Ny, bg = "white")
a.pack()

Clock(a,Nx,Ny)

root.mainloop()  #enter tkinter event loop

