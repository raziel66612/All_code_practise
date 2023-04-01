from math import *
from tkinter import *

#create Tk root widget
root = Tk()
root.title("graphlib0 v1.0")

#create Tk event loop
def MainLoop():
    root.mainloop()

def GraphInit(nxwin, nywin):
    global w,nxw,nyw

    nxw=nxwin; nyw=nywin    #setting size of canvas
    w = Canvas(root, width=nxw, height=nyw, bg="white")   #creating canvas
    w.pack()
    return W

def Nint(x): return int(floor(x+0.5))  # returning nearest integer

def Plot0(x,y,n,col,fxmin,fxmax,fymin,fymax,xtext,ytext,title):
    global w,nxw,nyw  #canvas object size

    xmin = min(x[1:n+1]); xmax = max(x[1:n+1])  #limits to user domain
    ymin = min(y[1:n+1]); ymax = max(y[1:n+1])  

    if(ymin == 0.0 and ymax == 0.0): ymin=-1e0 ; ymax= 1e0
    if(ymin == ymax): ymin *=0.9 ; ymax*=1.1

    ixmin = Nint(fxmin*nxw) ; ixmax=Nint(fxmax*nxw)        #canvas domain: x-axis
    iymin = Nint((1e0-fymin)*nyw) ; iymax=Nint((1e0-fymax)*nyw)  #canvas domain: y-axis
    w.create_rectangle(ixmin,iymax,ixmax,iymin)  # draw frame #canvas rectangle is create with canvas top-left corner x1,y1 and bottom_right corner as x2,y2 #create_rectangle(x1,y1,x2,y2)

    w.create_text((ixmin+ixmax)/2, iymin+10, text=xtext,anchor=N)  #x-axis title
    w.create_text((ixmin-10), (iymin+iymax)/2, text=ytext,anchor=E)  #y-axis title
    w.create_text((ixmin+ixmax)/2, iymax-10, text=title,anchor=S)  #plot title

    w.create_text(ixmin,iymin+10,text="{0:5.2f}".format(xmin), anchor=NW)
    w.create_text(ixmax,iymin+10,text="{0:5.2f}".format(xmax), anchor=NE)
    w.create_text(ixmin-10,iymin,text="{0:5.2f}".format(ymin), anchor=E)
    w.create_text(ixmin-10,iymax,text="{0:5.2f}".format(ymax), anchor=E)

    ax=(ixmax-ixmin)/(xmax-xmin) #scaling coefficient in x-axis
    bx=ixmin-ax*xmin 
    ay=(iymax-iymin)/(ymax-ymin) #scaling coefficient in y-axis
    by=iymin-ay*ymin

    #draw axis
    if(xmin*xmax<0): w.create_line(Nint(bx),iymin,Nint(bx),iymax)  #y-axis
    if(ymin*ymax<0): w.create_line(ixmin,Nint(by),ixmax,Nint(by)) #x-axis

    ix0 = Nint(ax*x[1]+bx) ; iy0=Nint(ay*y[1]+by) #draw first point
    for i in range(2,n+1):
        ix = Nint(ax*x[i]+bx); iy=Nint(ay*y[i]+by)   #new point
        w.create_line(ix0,iy0,ix,iy,fill=col)
        ix0=ix; iy0=iy  #save point to previous variable to draw next point



def Func(x):
    return (pow(x,3)*exp(-x))
# def Func(x):
#     return (pow(x,2))

#main
xmin=-0.8; xmax=7.8
# xmin=-10;xmax=10

n=50

x=[0]*(n+1)
y=[0]*(n+1)
h=(xmax-xmin)/(n-1) #argument spacing

for i in range(1,n+1):
    x[i]=xmin+(i-1)*h
    y[i]=Func(x[i])

GraphInit(800,600)  #create canvas

Plot0(x,y,n,"blue",0.15,0.95,0.15,0.85,"x","y","x^3*exp(-x)") #create plot

MainLoop()