#ifndef NETWORKING_H
#define NETWORKING_H

#include <ntcore.h>
#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTable.h>

#include <iostream>
class Networking{
    public:

        static Networking* getInstance();
        bool StartConfigServer(uint port);
        bool StopConfigServer();
        std::shared_ptr<nt::NetworkTable> GetConfigTable();
        bool SaveConfigPersistant();
        static void LogNTMessage(const nt::LogMessage &msg);
    private:
        static Networking* instance;
        nt::NetworkTableInstance ntInst;
        std::shared_ptr<nt::NetworkTable>ntTable = nullptr;
};
#endif