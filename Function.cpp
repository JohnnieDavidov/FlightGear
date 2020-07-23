//
// Created by zvi on 12/26/19.
//

#include "Function.h"
#include "Lexer.h"

extern Interpreter I;

Function :: Function(list<list<string>> commandList, vector<string> vars) {
    this->Vars = vars;
    this->CommandList = commandList;
}

void Function :: setVariables(list<string> num) {
    I.setVariables(this->Vars, num);
}

int Function :: execute() {
    Lexer l;
    l.parser(this->CommandList);
}