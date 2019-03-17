#pragma once
#include <iostream>
#include "networking.h"
#include <networktables/NetworkTableInstance.h>
#include "capture.h"
#include "ImgShowPipeline.h"
 int main(int argc, char *argv[]){
    ImgShowPipeline imgShow;
    Capture c;
    imgShow.enableStream("ImgShow", 5000);
    c.AddPipeline(&imgShow);
    c.StartCapture(2);
  
    while(true){}

    return 0;
}