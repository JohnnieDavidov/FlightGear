//
// Created by johnnie on 22/12/2019.
//

#ifndef FLIGHTGEAR_LEFTVAR_H
#define FLIGHTGEAR_LEFTVAR_H
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
#include "OpenServerCommand.h"
/*
 *this var will update the value from simulator.
 * (<-)
 */
class LeftVar {
    string m_path;
    string m_name;
    double m_val = 0;
public:
    LeftVar(string name, string path);
    void setVal(double);
    double getVal();
    string getPath();
};


#endif //FLIGHTGEAR_LEFTVAR_H
