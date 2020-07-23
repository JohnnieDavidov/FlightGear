//
// Created by johnnie on 22/12/2019.
//

#include "LeftVar.h"
//constructor
LeftVar::LeftVar(string name, string path) {
    this->m_name = name;
    this->m_path = path;
}
//setter
void LeftVar::setVal(double val) {
    this->m_val = val;
}
//getter
double LeftVar::getVal() {
    return m_val;
}
// get the path of the var
string LeftVar::getPath() {
    return this->m_path;
}