//
// Created by zvi on 12/26/19.
//

#ifndef FLIGHTGEAR_FUNCTION_H
#define FLIGHTGEAR_FUNCTION_H

#include <list>
#include "Command.h"
#include "Interpreter.h"

class Function: public Command {
    list<list<string>> CommandList;
    vector<string> Vars;
public:
    Function(list<list<string>> commandList, vector<string> vars);
    int execute() override ;
    void setVariables(list<string> num);
};


#endif //FLIGHTGEAR_FUNCTION_H
