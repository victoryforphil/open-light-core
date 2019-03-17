#include "networking.h"

bool Networking::StartConfigServer(uint port){
    std::cout << "[Networking/StartConfigServer] Starting Config NT Server on port: " << port <<std::endl;
    ntInst->Create();
    ntInst->AddLogger(LogNTMessage,nt::NetworkTableInstance::kLogDebug2, nt::NetworkTableInstance::kLogCritical);
    ntInst->StartServer("conf11ig_nt.ini","127.0.0.1", port);
    ntTable = ntInst->GetTable("openlight/config");
    ntTable->PutBoolean("started", true);
    return true;
}

std::shared_ptr<nt::NetworkTable> Networking::GetConfigTable(){
    return ntTable;
}

void Networking::LogNTMessage(const nt::LogMessage &msg){
  std::cout<<msg.logger<<std::endl;
}