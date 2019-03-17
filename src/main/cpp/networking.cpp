#include "networking.h"

Networking* Networking::instance = 0;

Networking* Networking::getInstance(){
  if(instance == 0){
    instance = new Networking();
  }

  return instance;
}

bool Networking::StartConfigServer(uint port){
    std::cout << "[Networking/StartConfigServer] Starting Config NT Server on port: " << port <<std::endl;
    ntInst = (nt::NetworkTableInstance)nt::GetDefaultInstance();
    
    ntInst.AddLogger(LogNTMessage,nt::NetworkTableInstance::kLogCritical, nt::NetworkTableInstance::kLogDebug4);
    ntInst.StartServer("1.ini","127.0.0.1", port);
    ntTable = ntInst.GetTable("openlight/config");
    ntTable->PutBoolean("started", true);
    

    std::cout << "[Networking/StartConfigServer] Start Status: " << ntTable->GetBoolean("started",false) << std::endl;

    std::cout << nt::GetDefaultInstance() << std::endl;
    
    
    return true;
}

std::shared_ptr<nt::NetworkTable> Networking::GetConfigTable(){
    return ntTable;
}

void Networking::LogNTMessage(const nt::LogMessage &msg){
  std::cout<<msg.logger<<std::endl;
}