#include <iostream>
#include <ntcore.h>
#include <networktables/NetworkTableInstance.h>
#include <thread>
int main(){
    nt::NetworkTableInstance inst = (nt::NetworkTableInstance)nt::GetDefaultInstance();

    inst.StartServer("test.ini","10.0.0.15",6666);
    
    std::shared_ptr<nt::NetworkTable> table = inst.GetTable("openlight");

    table->PutNumber("test", 12);
    

    std::cout << "Open Light > Lime Light" << std::endl;

    nt::NetworkTableInstance* instClient;
    instClient->Create();
    instClient->StartClient("10.0.0.15", 6666);
    while(!instClient->IsConnected()){
        //std::cout<<instClient->GetTable("openlight")->GetNumber("test",0);
    }
    std::cout <<"CONNECTED"<<std::endl;

    return 0;
}