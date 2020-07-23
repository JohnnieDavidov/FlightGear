//
// Created by zvi on 12/19/19.
//

#ifndef FLIGHTGEAR_LEXER_H
#define FLIGHTGEAR_LEXER_H

#include <list>
#include <string>
#include "OpenServerCommand.h"
#include "ConnectClientCommand.h"
#include <vector>
#include <unordered_map>
#include "RightVar.h"
#include "LeftVar.h"
#include "EqualVar.h"


using namespace std;

class Lexer {
OpenServerCommand* openServerCommand;

public:
    Lexer();
    list<list<string>> read(string file_name);
    void parser(list<list<string>> commandList);
    double interpret(string s);
};


#endif //FLIGHTGEAR_LEXER_H