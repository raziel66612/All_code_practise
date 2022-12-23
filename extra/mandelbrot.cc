#include<fstream>
#include<iostream>
using namespace std;

// int mandelbrot(double real,double img)
int mandelbrot(double cr,double ci)
{
    int limit=10000;
        // double c_real=0;
        // double c_img=0;
    // for (int i=0;i<limit;++i){
    //     c_real = real*real;
    //     c_img = img*img;
        
    //     if(c_real+c_img > 4.0) return i;

    //     c_img= img +2.0*c_real*c_img;
    //     c_real= real + c_real - c_img;  

    double zr=0.0 ,zi=0.0;
    for (int i=0; i<limit; ++i){
        if (zr*zr + zi*zi > 4.0) return i;
        double temp_zr = cr + zr*zr - zi*zi;
        zi = ci + 2.0*zr*zi;
        zr = temp_zr;
     
/*above equations comes from: 
(a+bi)^2 = a^2 + (b*i)^2 + 2*a*b*i 
where,
real part = a^2 - b^2;
imaginary part = 2*a*b*i;
*/
    }
    return limit;
}


int main()
{

double xmin,xmax,ymin,ymax,Nx,Ny,dx,dy;

Nx=512;  //total number of y nodes
Ny=250;  //total number of x nodes
xmin=-2.0; //limit on negative x axis(real axis)
xmax=2.0;  //limit on positive x axis(real axis)
ymin=-1.0;  //limit on negative y axis(img axis)
ymax=+1.0;  //limit on positive y axis(img axis)

ofstream fout("mandelbrot_set_2.ppm");    //using ppm for plotting, 
fout << "P3" << endl;   // "magic number" for defining ppm.
fout << Nx << " " << Ny << endl;  
fout << "256" << endl; //pixel's max RGB value

dx=((xmax-xmin)/(Nx));   //step size in x direction 
dy=((ymax-ymin)/(Ny));   //step size in x direction

//cout<< "dx is : " << dx ;       //test 
//cout << "\ndy is :  " << dy;    //test

for (int i=0; i<Ny; i++){
    for(int j=0;j<Nx;j++){
        double cx= xmin + j*dx;
        double cy= ymax - i*dy;

        int value = mandelbrot(cx,cy);

//        if (value == 100){cout << "1";}
/*         if (value >=10){cout<< " ";}
        else if(value < 4){cout<<"1";}
*/
        int r=((value*2)%256);
        int g=((value*3)%256);
        int b=((value*4)%256);
/*
        int r=((value)%256);
        int g=((value)%256);
        int b=((value)%256);
*/

        fout<< r << " " << g << " " << b << " ";
        }
fout << endl;
}
fout.close();
return 0;
}