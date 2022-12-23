#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

double fx(double x)  //defining arctan function
{
    double ans=4/(1+x*x);    
    return ans;
}

int main()
{
cout << endl <<"Value of Pie from Std lib : "<< M_PI <<endl;

// Declaring and initializing variables:
double xmin=0 ;  // min coordinate in abscisa
double xmax=1 ; //max coordindate in abscisa
int Nx=1000 ;  //number of grid points in x
double dx = (xmax-xmin)/Nx ;     //step-size i.e. grid length i.e. distance between two nodes on abscisa,

double x[Nx]{}, y[Nx]{} ;       // Creating empty arrays

for(int i=0 ; i<Nx ; i++){
x[i]= xmin + i*dx;   // marching in x grid points from x=0 to x=1
y[i] = fx(x[i]);    //values of f(x) at all grid points
//cout<< y[i] << endl;
}

double integral= 0;
for (int i=0; i < Nx; i++){
integral+=dx*((y[i]+y[i+1])/2);        // numerical rectangular integration .i.e. Mid-point Rule
}

cout<< "Calculated value of Pi : "<< integral << endl;
cerr << "Error : " << (M_PI - integral)*100 << " %"<< endl;
//cout<< fx;
return 0;
}