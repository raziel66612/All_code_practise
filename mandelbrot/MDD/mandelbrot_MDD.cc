#include<iostream>
#include<fstream>
int mandelbrot_set(double real,double img)
{
    int limit=1000;
    double zr=0.0 ,zi=0.0;
    for (int i=0; i<limit; ++i){
        if (zr*zr + zi*zi > 4.0)return i;
        double tmp = real + zr*zr - zi*zi;
        zi = img + 2.0*zr*zi;
        zr = tmp;

    }
    return limit;
}

int main()
{
double x_left,x_right,y_bottom,y_top,point_in_x,point_in_y,delta_x,delta_y;

  
x_left=-2.0; 
x_right=2.0;  
y_bottom=-1.0; 
y_top=+1.0;  
point_in_x=200;  
point_in_y=200;


delta_x=((x_right-x_left)/(point_in_x));    
delta_y=((y_top-y_bottom)/(point_in_y));

std::ofstream file("output_image.ppm");     
file << "P3" << std::endl;   
file << point_in_x << " " << point_in_y << std::endl;  
file << "256" << std::endl; 
   

int k = 0;     

for (int i=0; i<point_in_y; i++){
    for(int j=0;j<point_in_x;j++){
        double cx= x_left + j*delta_x;
        double cy= y_top - i*delta_y;

        int value = mandelbrot_set(cx,cy);

        if (value>100){
            ++k;
        }

        int r=(value%256);
        int g=(value%256);
        int b=(value%256);

        file<< r << " " << g << " " << b << " ";
        }

file << std::endl ;
}

double fraction =  (k)/(point_in_x*point_in_y);
double area = (fraction*(x_right-x_left))*(y_top-y_bottom);
std::cout<< "Area = " << area;

file.close();
return 0;
}