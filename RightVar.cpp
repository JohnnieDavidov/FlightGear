//
// Created by johnnie on 22/12/2019.
//
using namespace std;
#include "RightVar.h"
#include "EqualVar.h"
/*
 * update the new value to simulator.
 * send massage to client socket with new value.
 */
void RightVar::setVal(double val) {
    this->m_val = val;
    string massage = + "set " + this->m_path + " " + to_string(this->m_val) +" " + '\r' + '\n';
    connectCommand->sendToServer(massage);
}
//getter
double RightVar::getVal() {
    return this->m_val;
}
//constructor
RightVar::RightVar(string name, string path, ConnectClientCommand* connectCommand1) {
    this->m_name = name;
    this->m_path = path;
    this->connectCommand = connectCommand1;
}

string RightVar::getName() {
    return this->m_name;
}
