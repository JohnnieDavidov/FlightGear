//
// Created by zvi on 12/25/19.
//

#include "ConditionCommand.h"
#include "Lexer.h"

extern Interpreter I;

//constractor
ConditionCommand :: ConditionCommand(list<list<string>> commandList, string command,  string left, string sign, string right){
    this->CommandList = commandList;
    this->Command = command;
    this->Left = left;
    this->Sign = sign;
    this->Right = right;
}

//this function check if condition is true or false.
bool ConditionCommand ::condition() {
    if (Sign == "=" && I.interpret(Left) == I.interpret(Right)) {
        return true;
    } else if (Sign == "==" && I.interpret(Left) == I.interpret(Right)) {
        return true;
    } else if (Sign == ">" && I.interpret(Left) > I.interpret(Right)) {
        return true;
    } else if(Sign == "<" && I.interpret(Left) < I.interpret(Right)) {
        return true;
    } else if(Sign == ">=" && I.interpret(Left) >= I.interpret(Right)) {
        return true;
    } else if(Sign == "<=" && I.interpret(Left) <= I.interpret(Right)) {
        return true;
    } else if(Sign == "!=" && I.interpret(Left) != I.interpret(Right)) {
        return true;
    }
    //the condition is false.
    return false;
}

//this function execute if or while command
int ConditionCommand :: execute() {
    Lexer l = Lexer();
    if (this->Command == "if" && this->condition()) {
        l.parser(this->CommandList);
    } else if (this->Command == "while") {
        while (this->condition()) {
            l.parser(this->CommandList);
        }
    }
    return  0;
}