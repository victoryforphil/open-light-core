#pragma once
#include <cscore.h>
#include <vector>
#include <thread>
#include <string>
#include "pipeline.h"

class Capture{
    
    
    public:


        bool StartCapture(int cam);
        int  AddPipeline(Pipeline* pipeline);
        int  StreamPipeline(std::string name, char* streamname, int port);
       
        
    protected:
        std::vector<Pipeline*> pipelines;
        cv::Size2i  currentResolution;
        cs::UsbCamera* camera;
        cs::MjpegServer* server;
        void RunPipelines(cv::Mat inputFrame);
        void RunLoop();
        int pipelineIndex = 0;
};