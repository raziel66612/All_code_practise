#include <iostream>
using namespace std;

double* Vector(int x_min,int x_max)
//******************************************
//allocating memory for creating vector, using malloc  
//******************************************
{
double* p;

p = (double*) malloc((size_t) ((x_max - x_min + 1)*sizeof(double)));
if (!p){
    printf("cannot allocaete vector \n");
    exit(1);
}
return p-x_min;     // adjust for offset // by using shift of origin.
}

void DestroyVector(double* p,int x_min)
//******************************************
//Destroying the allocated memory to prevent memory leak  
//******************************************
{
    free((void*) (p + x_min));      //re-adjusting/compensating for offset
}


int main()
{
int xmin,xmax,ymin,ymax;
xmin =-1 ; xmax = +1;
ymin =-1 ; ymax = +1;

double* a = Vector(xmin,xmax) ; // testing created vector
        for(int i=xmin; i<=xmax; i++) a[i]=i;

        for(int i=0;i<=xmax;i++){
            cout << " array index: " << i << ";   array value : " << a[i] << endl;  
        }

cout<< endl <<"testing \n1\n2\n3" <<endl;
    return 0;
}
