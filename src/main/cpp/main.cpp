#pragma once
#include <iostream>
#include "networking.h"
#include <networktables/NetworkTableInstance.h>
#include "capture.h"
#include "ImgShowPipeline.h"
 int main(int argc, char *argv[]){

   
    Networking::getInstance()->StartConfigServer(7777);

    ImgShowPipeline imgShow;
    Capture c;
    c.AddPipeline("Image Show", &imgShow);
    c.StreamPipeline("Image Show", 5000);
    c.StartCapture(2);
    
    while(true){}

    return 0;
}