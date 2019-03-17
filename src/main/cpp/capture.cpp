#include "capture.h"

bool Capture::StartCapture(int cam)
{
    camera = new cs::UsbCamera("InputCam", cam);
    camera->SetVideoMode(cs::VideoMode::kMJPEG, 320, 240, 30);

    server = new cs::MjpegServer("httpserver", 8081);
    server->SetSource(*camera);

    cs::CvSink cvsink{"cvsink"};
    cvsink.SetSource(*camera);
    cv::Mat inFrame;
    for (;;)
    {
        uint64_t time = cvsink.GrabFrame(inFrame);
        if (time == 0)
        {
            std::cout << "error: " << cvsink.GetError() << std::endl;
            continue;
        }
        std::cout << "got frame at time " << time << " size " << inFrame.size()
                  << std::endl;
        RunPipelines(inFrame);

    }
    return true;
}

void Capture::RunPipelines(cv::Mat inputFrame){
    for(int i=0;i<pipelines.size();i++){
        pipelines[i]->runPipeline(inputFrame);
    }
}

int Capture::AddPipeline(Pipeline* pipeline){
    pipelines.push_back(pipeline);
    pipelineIndex++;
    return pipelineIndex -1;
}

