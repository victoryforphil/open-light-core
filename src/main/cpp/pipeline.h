#ifndef PIPELINE_H
#define PIPELINE_H
#include <opencv2/opencv.hpp>
#include <cscore.h>
#include <string>
class Pipeline{
    public:
        cv::Mat runPipeline(cv::Mat inputFrame);
        void enableStream(std::string name, int port);
    protected:
        virtual cv::Mat process(cv::Mat) = 0;

    private: 
        bool bStream = false;
        cs::MjpegServer* server;
        cs::CvSource* source;
};
#endif