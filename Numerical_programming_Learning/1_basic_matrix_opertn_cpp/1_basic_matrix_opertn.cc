#include <iostream>
using namespace std;

double** Matrix(int x_min,int x_max,int y_min, int y_max)
//*******************************************************
//allocating memory for creating matrix, using malloc  
//*******************************************************
{
int i;
int Nx = x_max - x_min ;
int Ny = y_max - y_min ; 
double** p;

p = (double**) malloc((size_t) (Nx*sizeof(double*)));
if (!p){
    printf("Cannot allocate : 1st Dimension \n");
    exit(1);
}
p-=x_min;     // adjust for offset // by using shift of origin.

p[x_min] = (double*) malloc((size_t) (Nx*Ny*sizeof(double)));
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
//*******************************************************
//Destroying the allocated memory to prevent memory leak  
//*******************************************************
{
    free((void*) (p[x_min] + y_min));
    free((void*) (p + x_min));      //
    cout << "Matrix Destroyed"<< endl ;
}

// --------------------------- MAIN ---------------------------
int main()
{
int xmin,xmax,ymin,ymax;
xmin =-2 ; xmax = +2;
ymin =-2 ; ymax = +2;

double** A = Matrix(xmin,xmax,ymin,ymax);
for (int i= xmin ; i<=xmax ; i++){
    for (int j= ymin ; j<=ymax ; j++)
    { 
        A[i][j] = i*j ; 
        cout << A[i][j] << "   " ;
    }
cout<< endl ;
}

DestroyMatrix(A,xmin,ymin);
// cout<< endl <<"testing \n1\n2\n3" <<endl;
    return 0;
}
