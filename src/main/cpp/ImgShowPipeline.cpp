#include "ImgShowPipeline.h"

cv::Mat ImgShowPipeline::process(cv::Mat input){
    //cv::imshow("Img Show Pipeline", input);
    cv::Mat out;
    cv::cvtColor(input.clone(), out, cv::COLOR_BGR2GRAY);
    return out;
}