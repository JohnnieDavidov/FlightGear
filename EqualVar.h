//
// Created by johnnie on 23/12/2019.
//

#ifndef FLIGHTGEAR_EQUALVAR_H
#define FLIGHTGEAR_EQUALVAR_H
using namespace std;
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <array>
#include <unordered_map>
#include <cstdlib>
#include <mutex>
#include <thread>
#include <chrono>

class EqualVar {
    string m_name;
    double m_val = 0;

public:
    EqualVar(string name, double val);
    void setVal(double);
    double getVal();
};


#endif //FLIGHTGEAR_EQUALVAR_H
