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
       // std::cout << "got frame at time " << time << " size " << inFrame.size()
         //         << std::endl;
        RunPipelines(inFrame);

    }
    return true;
}
void Capture::UpdateResolution(int width, int height){
    currentResolution.width = width;
    currentResolution.height = height;
}
void Capture::RunPipelines(cv::Mat inputFrame){
    std::map<std::string, Pipeline*>::iterator itr;

    for(itr = pipelines.begin(); itr != pipelines.end(); ++itr){
        itr->second->runPipeline(inputFrame);
    }
}

int Capture::AddPipeline(std::string name, Pipeline* pipeline){
    std::cout << "[Capture/AddPipeline] Adding pipeline: " << name << std::endl;
    
    pipelines.insert(std::pair<std::string, Pipeline*>(name, pipeline));
   
    pipelineIndex++;

    Networking::getInstance()->GetConfigTable()->PutBoolean("pipelines/"+name+"/enabled", true);
    Networking::getInstance()->GetConfigTable()->PutBoolean("pipelines/"+name+"/streaming", false);
    Networking::getInstance()->GetConfigTable()->PutNumber("pipelines/"+name+"/port", 0000);
    return pipelineIndex -1;
}

int Capture::StreamPipeline(std::string name, int port){
    std::cout << "[Capture/StreamPipeline] Starting stream for pipeline: " << name << " on port: " << port << std::endl;
    Pipeline* pipelineToStream = pipelines[name];
    pipelineToStream->enableStream(name, port);
    Networking::getInstance()->GetConfigTable()->PutBoolean("pipelines/"+name+"/streaming", true);
    Networking::getInstance()->GetConfigTable()->PutNumber("pipelines/"+name+"/port", port);
    Networking::getInstance()->GetConfigTable()->PutString("pipelines/"+name+"/stream_url", "localhost:"+std::to_string(port)+"/stream.mjpg");
}