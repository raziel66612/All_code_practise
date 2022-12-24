#include <iostream>
using namespace std;

double** Matrix(int x_min,int x_max,int y_min, int y_max)
//*******************************************************
//allocating memory for creating matrix, using malloc  
//*******************************************************
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
//*******************************************************
//Destroying the allocated memory to prevent memory leak  
//*******************************************************
{
    free((void*) (p[x_min] + y_min));  // de-allocate block
    free((void*) (p + x_min));      //   de-allocate array of row pointers
    cout << "Matrix Destroyed"<< endl ;
}

// --------------------------- MAIN ---------------------------
int main()
{
int xmin,xmax,ymin,ymax;
xmin =-1 ; xmax = +1;
ymin =-1 ; ymax = +1;

double** A = Matrix(xmin,xmax,ymin,ymax);

// A={{1, 2, 3}, {4, 5, 6}, {7,8,9}};   //cannot allocate like this, you need to acces each space individually to assign or operate on that value

// allocating values below.
for (int i= xmin ; i<=xmax ; i++){
    for (int j= ymin ; j<=ymax ; j++)
    { 
       A[i][j] = i*j ; 
        cout << A[i][j] << "   " ;
    }
cout<< endl ;
}
cout<< "Total size is : " << sizeof(A) <<endl;
DestroyMatrix(A,xmin,ymin);
// cout<< endl <<"testing \n1\n2\n3" <<endl;
    return 0;
}
