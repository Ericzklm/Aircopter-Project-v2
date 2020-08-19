#include "mbed.h"
#include "sensor_fusion.h"
#include "quaternion.h"
#include "millis.h"



MPU6050 MPU(D4,D5);
Serial pc(USBTX, USBRX); //create a Serial object
Timer timer;

int main() {
    MPU.start();
    timer.start();
    pc.baud(115200);
    float t;
    float mag;
    float pi = 3.14159265358979;
    int i=0;
    float sumgx,sumgy,sumgz,sumax,sumay,sumaz;
    float biasgx,biasgy,biasgz,biasax,biasay,biasaz;
    float gx,gy,gz,ax,ay,az;
    
    vector n;
    n.x=0;
    n.y=0;
    n.z=1;
    
    vector pointv;
    pointv.x=0;
    pointv.y=0;
    pointv.z=1;
    
    
    while(i<=19) 
    {
            
        if (MPU.data_ready() == 1) 
        {
            MPU.read_raw(&gx,&gy,&gz,&ax,&ay,&az);
            sumgx+=gx;
            sumgy+=gy;
            sumgz+=gz;
            sumax+=ax;
            sumay+=ay;
            sumaz+=az;
        } 
    i++;
    }
                biasgx=sumgx/20;
                biasgy=sumgy/20;
                biasgz=sumgz/20;
                biasax=sumax/20;
                biasay=sumay/20;
                biasaz=sumaz/20;        
               
    while(i<=100)
    {
        if (MPU.data_ready() == 1) 
        {
            MPU.read_raw(&gx,&gy,&gz,&ax,&ay,&az);
            gx=gx-biasgx;
            gy=gy-biasgy;
            gz=gz-biasgz;
            ax=ax-biasax;
            ay=ay-biasay;
            az=az-biasaz +16384;
               /*
                pc.printf("%f\n\r", gx);
                pc.printf("%f\n\r", gy);
                pc.printf("%f\n\r", gz);
                pc.printf("%f\n\r", ax);
                pc.printf("%f\n\r", ay);
                pc.printf("%f\n\r", az);*/
                
        }   
            //pc.printf("%f \r\n", ax);
            vector initial; 
            initial.x = ax;
            initial.y = ay;
            initial.z = az;
            vector unit;
            vector_normalize(&initial,&unit);
//checkpoint 3
               

            
            vector v;
            t=(timer.read_ms())/1000.0;
            timer.reset();
            v.x= gx;
            v.y= gy;
            v.z= gz;

            quaternion q;
            vector unitv;
            vector compfilter;
            vector alphainitial;
            vector alphanrotate;
            vector nrotate;
            vector pointvunit;
           
            mag = -((vector_normalize(&v,&unitv))/(2952.0))*(t*pi);
            quaternion_create(&unitv, mag, &q);
            quaternion_rotate(&pointv,&q, &pointv);
            vector_normalize(&pointv,&pointvunit);
//checkpoint 4

            
            //n = normalize(𝛼a + (1 - 𝛼)rotate(n))
            vector_multiply(&initial,.1,&alphainitial);
            quaternion_rotate(&n,&q,&nrotate);
            vector_multiply(&nrotate,.9,&alphanrotate);
            vector_add(&alphainitial,&alphanrotate, &compfilter);
            vector_normalize(&compfilter, &n);
//checkpoint 5
            
            pc.printf("%f %f %f %f %f %f %f %f %f\r\n", unit.x,unit.y,unit.z,pointvunit.x,pointvunit.y,pointvunit.z,n.x,n.y,n.z);
            wait_ms(100);

            
    }
        i++;
        timer.reset(); 




}
