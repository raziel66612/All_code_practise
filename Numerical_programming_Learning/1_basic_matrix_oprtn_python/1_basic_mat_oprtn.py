from math import *
from random import *


"""
In the MatPrint function, the loop is designed to iterate over the elements of a 2D matrix with dimensions n x m,
where the indices start from 1 to n and 1 to m.
This is likely because the input matrix a has been created with an extra row and an extra column (i.e., with dimensions n+1 x m+1) using the following code:

#scss
#Copy code
#a=[[0]*(m+1) for i in range(n+1)]
The extra row and column might have been added for various reasons, 
such as to simplify the implementation of certain algorithms or to accommodate special boundary conditions.

Therefore, when printing the elements of the matrix using the MatPrint function,
the loop variable i should start from 1 and go up to n, and the loop variable j should start from 1 and go up to m.
This will ensure that only the elements of the actual n x m matrix are printed, and not the extra row and column.

If you try to loop from 0 to n and 0 to m, you will end up printing the extra row and column as well, which may not be desired.
"""

def MatPrint(a,m,n):
    for i in range(1,m+1):
        for j in range (1,n+1): print('{0:11.2e}'.format(a[i][j]), end="")
        print()


def MatProd(a,b,c,m,n,l):
    for i in range(1,m+1):
        for j in range(1,n+1):
            t=0e0
            for k in range(1,l+1): t+=a[i][k]*b[k][j]
            c[i][j] = t

def MatTrans(a,m,n):
    for i in range(1,m+1):
        for j in range(n+1):
            temp=a[i][j]; a[i][j] = a[j][i]; a[j][i]= temp


def MatDiff(a,b,c,m,n):
    for i in range(1,m+1):
        for j in range(n+1):
            c[i][j] = a[i][j] - b[i][j]

def MatAdd(a,b,c,m,n):
    for i in range(1,m+1):
        for j in range(n+1):
            c[i][j] = a[i][j] + b[i][j]

def MatNorm(a,m,n):
    norm = 0e0
    for i in range(1,m+1):
        for j in range(1,n+1):
            if(norm < fabs(a[i][j])): norm = fabs(a[i][j])
    return norm 

#a=[[1, 2],[2, 1]]
#MatPrint(a)


#Main program
m= int (input("No. of elements in row, m = "))
n= int (input("No. of elements in column, n = "))

#defining arrays of length n 
#array indices start at 0 and not 1 in all programming language including python, (except MATALAB, where indices starts with 1)
A=[[0]*(n+1) for i in range(m+1)]
B=[[0]*(n+1) for i in range(m+1)]
C=[[0]*(n+1) for i in range(m+1)]
D=[[0]*(n+1) for i in range(m+1)]

"""
Understanding Above Python code:
This Python syntax creates a two-dimensional list (or matrix) A with (m+1) rows and (n+1) columns,
where m and n are variables that should have been defined earlier.
Each element of the matrix A is initialized to 0 using the expression [0]*(n+1), which creates a list of (n+1) zeros,
and this expression is repeated (m+1) times using the list comprehension [0]*(n+1) for i in range(m+1) to create the matrix.

So, after executing this code, A[0][0] to A[m][n] will all be 0.
"""
"""
Note:  It can use either row-major or column-major ordered arrays, but it defaults to row-major ordering.
    that means by default whatever array you create, by default row vector is created. 

similarly,Programming languages and environments typically assume a single array layout for all data.
    MATLAB and Fortran use column-major layout by default, whereas C and C++ use row-major layout.
"""

#assigning random values to m x n matrix
for i in range(1,m+1):
    for j in range(1,n+1): A[i][j]= random() 
print("Matrix A =" )
MatPrint(A,m,n)
print() 
print("A[0][0]=",A[0][0])
print("A[1][1]=",A[1][1])
print()
"""
By default, the print() function in Python adds a newline character (\n) at the end of the output,
which means that each time you call the print() function, the output will be printed on a new line.

You can also explicitly add a newline character to the end of the output using the escape character \n, like this:
"""

for i in range(1,m+1):
    for j in range(1,n+1): B[i][j] = random()
MatPrint(B,m,n)
print()

if m==n:
    MatProd(A,B,C,m,m,m)
else:
    print("Need a square matrix to perform matrix product, please verify that 'm = n'")

print("Product C matrix is :")
MatPrint(C,m,n)

MatAdd(A,B,D,m,n)
print(" A + B = ")
MatPrint(D,m,n)


print(" Norm of A+B is = ",MatNorm(D,m,n))