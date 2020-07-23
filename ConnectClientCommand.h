//
// Created by johnnie on 22/12/2019.
//

#ifndef FLIGHTGEAR_CONNECTCLIENTCOMMAND_H
#define FLIGHTGEAR_CONNECTCLIENTCOMMAND_H

#include "Command.h"
class ConnectClientCommand : public Command {
private:
    int m_port;
    string m_ip;
    int m_fd{};

public:
    ConnectClientCommand(string server_ip, double server_port);
    int execute() override;
    //returns -1 if could not send
    void sendToServer(string massage);
    void closeConnection();
};


#endif //FLIGHTGEAR_CONNECTCLIENTCOMMAND_H
