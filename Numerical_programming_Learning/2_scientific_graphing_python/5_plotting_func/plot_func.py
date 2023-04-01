from math import *
from graph0 import *

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