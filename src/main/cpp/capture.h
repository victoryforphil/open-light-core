#pragma once
#include <cscore.h>
#include <vector>
#include <thread>
#include <string>
#include "pipeline.h"
#include <map> 
#include "networking.h"
class Capture{
    
    
    public:


        bool StartCapture(int cam);
        int  AddPipeline(std::string name, Pipeline* pipeline);
        int  StreamPipeline(std::string name, int port);
        void UpdateResolution(int width, int height);
        
    protected:
        std::map<std::string, Pipeline*> pipelines;
        cv::Size2i  currentResolution;
        cs::UsbCamera* camera;
        cs::MjpegServer* server;
        void RunPipelines(cv::Mat inputFrame);
        void RunLoop();
        int pipelineIndex = 0;
};