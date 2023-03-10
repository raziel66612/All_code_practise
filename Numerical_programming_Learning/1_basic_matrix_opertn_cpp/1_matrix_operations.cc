#ifndef _MATUTIL_
#define _MATUTIL_

#include <iostream>
#include <stdio.h>
#include "math.h"


using namespace std;

double** Matrix(int x_min,int x_max,int y_min, int y_max)
{
int i;
int Nx = x_max - x_min + 1 ;
int Ny = y_max - y_min + 1 ; 
double** p;

p = (double**) malloc((size_t) (Nx*sizeof(double*)));   // allocate array of row pointers
if (!p){
    printf("Cannot allocate : 1st Dimension \n");
    exit(1);
}
p-=x_min;     // adjust for offset // by using shift of origin.

p[x_min] = (double*) malloc((size_t) (Nx*Ny*sizeof(double)));   //assign block start to 1st row pointer,i.e. pointer to pointers
if (!p){
    printf("Cannot allocate : 2nd Dimension \n");
    exit(2);
} else {
    cout<< "Matrix created " << endl;
}

p[x_min]-=y_min;
for (i=x_min+1 ; i<=x_max ; i++)  p[i]=p[i-1] + Ny;

return p;
}

void DestroyMatrix(double** p,int x_min, int y_min)
{
    free((void*) (p[x_min] + y_min));  // de-allocate block
    free((void*) (p + x_min));      //   de-allocate array of row pointers
    cout << "Matrix Destroyed"<< endl ;
}

void MatrixNull(double** p,int x_min, int x_max,int y_min,int y_max)       // allocating values.
{
for (int i= x_min ; i<=x_max ; i++)
    for (int j= y_min ; j<=y_max ; j++)  p[i][j] = 0 ; 
}

void MatrixRandCreate(double** p,int x_min, int x_max,int y_min,int y_max)   //create a random matrix
{
    for (int i= x_min ; i<=x_max ; i++)
        for (int j= y_min ; j<=y_max ; j++)  p[i][j] = rand()/(RAND_MAX+1e0) ;
}


void MatrixPrint(double** p,int x_min, int x_max,int y_min,int y_max)    //print out matrix
{             
    for (int i= x_min ; i<=x_max ; i++){
        for (int j= y_min ; j<=y_max ; j++) printf("%12.2e",p[i][j]) ;
    cout<< endl ;
}
}

void MatrixTranspose(double** p,int x_min, int x_max,int y_min,int y_max){
    double temp;
    int i,j;
    for (i=x_min+1; i<=x_max; i++)
        for (j = y_min; j<=y_max ; j++) {
            temp = p[i][j] ;
            p[i][j] = p[j][i] ;
            p[j][i] = temp ;
        }
}

void MatrixSubtraction(double** p, double** q, double** r, int x_min, int x_max,int y_min,int y_max){
    for (int i=x_min; i<=x_max; i++)
        for (int j = y_min; j<=y_max ; j++) {
            r[i][j]= p[i][j] - q[i][j];
        }
}

void MatrixAddition(double** p, double** q, double** r, int x_min, int x_max,int y_min,int y_max){
    for (int i=x_min; i<=x_max; i++)
        for (int j = y_min; j<=y_max ; j++) {
            r[i][j]= p[i][j] + q[i][j];
        }
}

void MatrixProduct(double** p, double** q, double** r, int x_min, int x_max,int y_min,int y_max){
    // int Ny = y_max-y_min+1;
    for (int i=x_min; i<=x_max; i++)
        for (int j = y_min; j<=y_max ; j++) {
            double temp=0e0 ;
            for(int k=y_min; k<=y_max; k++)  temp += p[i][k] * q[k][j];
                // temp += p[i][k] * q[k][j];
            r[i][j] = temp;
        }
}

double MatrixNorm(double** p,int x_min, int x_max,int y_min,int y_max){     // return max|a[i][j]|
    double norm = 0e0;
    for (int i=x_min; i<=x_max; i++)
        for (int j = y_min; j<=y_max ; j++) {
            if(norm < (fabs(p[i][j]))) norm = fabs(p[i][j]); 
        }
    return norm;
}



void templatee(double** p,int x_min, int x_max,int y_min,int y_max)     //simple template to create functions
{
    for (int i=x_min; i<=x_max; i++)
        for (int j = y_min; j<=y_max ; j++) {

        }
}


// --------------------------- MAIN ---------------------------
int main()
{
int xmin,xmax,ymin,ymax;
xmin =-1 ; xmax = +1;
ymin =-1 ; ymax = +1;

double** A = Matrix(xmin,xmax,ymin,ymax);
double** B = Matrix(xmin,xmax,ymin,ymax);
double** C = Matrix(xmin,xmax,ymin,ymax);


MatrixRandCreate(A,xmin,xmax,ymin,ymax);  // create a random matrix A
cout<< "MAT A : " <<endl;
MatrixPrint(A,xmin,xmax,ymin,ymax);

MatrixRandCreate(B,xmin,xmax,ymin,ymax);  // create a random matrix B
cout<< "MAT B : " <<endl;
MatrixPrint(B,xmin,xmax,ymin,ymax);

MatrixNull(C,xmin,xmax,ymin,ymax);  // Allocate Null values to natrix C
cout<< "Null MAT C : " <<endl ;
MatrixPrint(C,xmin,xmax,ymin,ymax);
cout <<endl <<endl;


MatrixProduct(A,B,C,xmin,xmax,ymin,ymax);
cout<< "MAT C (i.e. C = A*B) : " <<endl;
MatrixPrint(C,xmin,xmax,ymin,ymax);

MatrixAddition(A,B,C,xmin,xmax,ymin,ymax);
cout<< "MAT C (i.e. C = A+B) : " <<endl;
MatrixPrint(C,xmin,xmax,ymin,ymax);

MatrixSubtraction(A,B,C,xmin,xmax,ymin,ymax);
cout<< "MAT C (i.e. C = A-B) : " <<endl;
MatrixPrint(C,xmin,xmax,ymin,ymax);

MatrixTranspose(A,xmin,xmax,ymin,ymax);
cout<<"Max random value is : " <<RAND_MAX+1e0 << endl << "Tranpose of A is " << endl;
MatrixPrint(A,xmin,xmax,ymin,ymax);

double norm_is = MatrixNorm(A,xmin,xmax,ymin,ymax);

DestroyMatrix(A,xmin,ymin);
DestroyMatrix(B,xmin,ymin);
DestroyMatrix(C,xmin,ymin);
cout<< endl << "Norm is : " << norm_is <<endl;
    return 0;
}

#endif