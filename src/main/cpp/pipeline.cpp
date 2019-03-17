#include "pipeline.h"

cv::Mat Pipeline::runPipeline(cv::Mat input){
    
    cv::Mat processed = process(input);
    if(bStream && source != nullptr){
        source->PutFrame(processed);
    }

    return processed;
}

void Pipeline::enableStream(std::string name, int port){
    server = new cs::MjpegServer(name,port);
    source  = new cs::CvSource(name,cs::VideoMode::kMJPEG,320, 240, 30);
    server->SetSource(*source);
    bStream = true;
}