from math import *

def MatPrint(a,n,m):
    for i in range(1,n+1):
        for j in range (1,m+1): print('{0:11.2e}'.format(a[i][j]), end="")
        print()

a=[[1, 2],[2, 1]]

MatPrint(a)

