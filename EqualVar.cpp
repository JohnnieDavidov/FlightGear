//
// Created by johnnie on 23/12/2019.
//

#include "EqualVar.h"
//constructor
EqualVar::EqualVar(string name, double val) {
    this->m_val = val;
    this->m_name = name;

}
//setter
void EqualVar::setVal(double val) {
    this->m_val = val;
}
//getter
double EqualVar::getVal() {
    return this->m_val;
}
