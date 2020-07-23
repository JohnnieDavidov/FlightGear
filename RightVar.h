//
// Created by johnnie on 22/12/2019.
//

#ifndef FLIGHTGEAR_RIGHTVAR_H
#define FLIGHTGEAR_RIGHTVAR_H
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <array>
#include <unordered_map>
#include <stdlib.h>
#include <mutex>
#include <thread>
#include <chrono>
#include "ConnectClientCommand.h"

/*
 * this var will update the simulator
 * if we change the value. (->).
 */
class RightVar {
    string m_name;
    string m_path;
    double m_val = 0;
    ConnectClientCommand *connectCommand;
public:
    RightVar(string name, string path, ConnectClientCommand *connectCommand1);
    void setVal(double);
    double getVal();
    string getName();
};

#endif //FLIGHTGEAR_RIGHTVAR_H
