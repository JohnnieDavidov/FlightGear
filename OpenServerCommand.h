
#ifndef FLIGHTGEAR_OPENSERVERCOMMAND_H
#define FLIGHTGEAR_OPENSERVERCOMMAND_H

#include "Command.h"
#include "LeftVar.h"

extern bool connected;

class OpenServerCommand : public Command{
private:
    int m_port;
    int m_fd;
    int m_socketFd;
    array<double, 36> m_array;
    unordered_map<string, double > m_map;

public:
    explicit OpenServerCommand(double port);
    int execute() override ;
    void getInfoAboutSim();
    int readFromSim();
    int insertBufferToMap(char* buffer, int buffer_len);
    void closeServer();
};


#endif //FLIGHTGEAR_OPENSERVERCOMMAND_H
