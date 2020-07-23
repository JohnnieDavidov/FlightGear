#include <iostream>
#include "ConnectClientCommand.h"
#include "OpenServerCommand.h"
#include "Lexer.h"
#include "RightVar.h"
#include "LeftVar.h"
#include "Function.h"


using namespace std;

//global data
unordered_map<string, RightVar*> rightMap;
unordered_map<string, LeftVar*> leftMap;
unordered_map<string, EqualVar*> equalMap;
unordered_map<string, Function*> funcMap;
vector<thread*> m_thread_vector;
Interpreter I;
bool connected = false;
ConnectClientCommand* connectClientCommand;

int main(int argc, char **argv) {
    Lexer l = Lexer();
    list<list<string>> commandList = l.read(argv[1]);
    //run
    l.parser(commandList);
    //close the server
    connected = false;
    //close the client
    connectClientCommand->closeConnection();
    //free all memory
    for(unordered_map<string, RightVar*>::iterator it = rightMap.begin(); it != rightMap.end(); it++) {
        free(it->second);
    }
    for(unordered_map<string, LeftVar*>::iterator it = leftMap.begin(); it != leftMap.end(); it++) {
        free(it->second);
    }
    for(unordered_map<string, EqualVar*>::iterator it = equalMap.begin(); it != equalMap.end(); it++) {
        free(it->second);
    }
    for(unordered_map<string, Function*>::iterator it = funcMap.begin(); it != funcMap.end(); it++) {
        free(it->second);
    }
    for (unsigned int i = 0; i < m_thread_vector.size(); i++) {
        free(m_thread_vector[i]);
    }
    return 0;

}