#include"../_pid.h"
#include<iostream>
#include<string.h>

int main(){
    //Setup Object
    PROPORTIONAL_INTEGRAL_DERIVATIVE *pObj = new PROPORTIONAL_INTEGRAL_DERIVATIVE();
    pObj -> createPIDinstance("testInstance",0.5,0.1,0.3);
    //Run API
    double res = pObj -> PID_MAIN("testInstance", 70, 90);
    std::cout << res << std::endl;
}