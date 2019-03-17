#include <ntcore.h>
#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTable.h>

#include <iostream>
class Networking{
    public:
        bool StartConfigServer(uint port);
        bool StopConfigServer();
        std::shared_ptr<nt::NetworkTable> GetConfigTable();
        bool SaveConfigPersistant();
        static void LogNTMessage(const nt::LogMessage &msg);
    private:
        nt::NetworkTableInstance* ntInst;
        std::shared_ptr<nt::NetworkTable>         ntTable = nullptr;
};
