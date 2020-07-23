//
// Created by zvi on 12/19/19.
//

#include "Command.h"
#include "Lexer.h"
#include "Interpreter.h"
#include <fstream>
#include <string>
#include "RightVar.h"
#include "LeftVar.h"
#include "EqualVar.h"
#include "ConditionCommand.h"
#include "Function.h"
#include <unordered_map>
#include <thread>

using namespace std;

//global data
extern unordered_map<string, RightVar*> rightMap;
extern unordered_map<string, LeftVar*> leftMap;
extern unordered_map<string, EqualVar*> equalMap;
extern unordered_map<string, Function*> funcMap;
extern vector<thread*> m_thread_vector;
extern Interpreter I;
extern ConnectClientCommand* connectClientCommand;

/// return if the string is a condition operator
bool isOperator(string s) {
    if (s == "=" || s == "==" || s == "<=" || s == ">=" || s == "!=" || s == "<" || s == ">") {
        return true;
    }
    return false;
}

// return the line without the word.
string eraseWord(string line, string word){
    string newLine = "";
    // num of " or ' ' we sould to remove.
    int add = 1;
    if (line[0] == '"') {
        add++;
    }
    // copy the new erase line to temp string called newLine
    for (unsigned int i = word.length() + add; i < line.length(); i++) {
        newLine += line[i];
    }
    return newLine;
}

//erase the latest char of word;
string eraseEnd(string word) {
    string newWord = "";
    unsigned int i;
    for (i = 0; i < word.length() - 1; i++) {
        newWord += word[i];
    }
    return newWord;
}

//erase first char of word
string eraseFirst(string word) {
    string temp = "";
    for (unsigned int i = 1; i < word.length(); i++) {
        temp += word[i];
    }
    return  temp;
}

//if don't have space, add space.
string addSpace(string line) {
    int comma = 0;
    string spaceLine = "";
    for (unsigned int i = 0; i < line.length(); i++) {
        //check if comma is open. if open close = 0, else open = 1.
        if(line[i] == '"') {
            if (comma) {
                comma = 0;
            } else {
                comma = 1;
            }
        }
        //condition for space before char
        if ((!comma) &&
            ((line[i] == '=' && line[i-1] != '<' && line[i+1] != '>' && line[i-1] != '>' && line[i-1] != '!' &&
            line[i-1] != '=') || line[i] == '<'  || (line[i] == '>' && (line[i-1] != '-' && line[i+1] != '=' &&
            line[i-1] != '=')) || (line[i] == '-' && line[i+1] == '>')) && line[i - 1] != ' ') {
            spaceLine += ' ';
        }
        //add char
        spaceLine += line[i];
        //condition for space after char
        if ((line[i] == '=' && line[i+1] != '>' && line[i+1] != '=') || (line[i] == '<' && (line[i+1] != '-'&&
        line[i+1] != '=')) || (line[i] == '>' && line[i+1] != '=' && line[i-1] != '=') && (line[i + 1] != ' ')) {
            spaceLine += ' ';
        }
    }
    return spaceLine;
}

//remove space in expression
string removeSpace(string word) {
    string temp = "";
    for (unsigned int i = 0; i < word.length(); i++) {
        if (word[i] != ' ') {
            temp += word[i];
        }
    }
    return temp;
}

// return the first word of the line (until there is a space)
string readWord(string line) {
    string first = "";
    int i = 0;
    while ((line[i] != ' ' || line[0] == '"' || (line[0] >= '0' && line[0] <= '9')) &&
           line[i] != '(' && line[i] != ')' && line[i] != ',' && line.length() != first.length() &&
           line[i] != '\t' && line[i] != '{') {
        first += line[i];
        i++;
    }
    //erase " "
    if (first[0] == '"' || first[first.length()-1] == '"') {
        string temp = "";
        int i = 0;
        int num = 0;
        while (first.length() != temp.length() - num) {
            if (first[i] != '"') {
                temp += first[i];
                i++;
            } else {
                if(i != 0) {
                    break;
                }
                i++;
                num++;
            }
        }
        first = temp;
    }
    return first;
}

//empty constractor
Lexer :: Lexer() {
}

//read the file and lexer to list.
list<list<string>> Lexer :: read(string file_name) {
    //open file
    fstream file;
    file.open(file_name);
    if (!file.is_open()) {
        throw "Error in open file " + file_name;
    }
    // create list of list *it->begin() command
    list<list<string>> commandList;
    string line;
    while (getline(file, line)) {
        line = addSpace(line);
        list<string> command;
        while (line.length() != 0 && line != ")") {
            string word;
            if (command.size() != 0 && (isOperator(command.back()) || command.back() == "Sleep")) {
                word = line;
                //remove space
                while (word[0] == ' ') {
                    word = eraseFirst(word);
                    line = eraseFirst(line);
                }
                //erase { if in the end of string
                if(word[word.length() - 1] == '{' || (command.back() == "Sleep" && word[word.length() - 1] == ')')) {
                    word = eraseEnd(word);
                }
                while (word[word.length() - 1] == ' ') {
                    word = eraseEnd(word);
                    line = eraseEnd(line);
                }
                word = removeSpace(word);
                line = removeSpace(line);
                //end remove space
            } else {
                word = readWord(line);
            }
            line = eraseWord(line, word);
            //remove space in expression
            if(word[0] >= '0' && word[0] <= '9') {
                word = removeSpace(word);
            }
            //condition if there is expression
            if (((command.size() > 0) && (*(command.begin()) == "connectControlClient" || *(command.begin()) == "Sleep")
                || (word == "Sleep") || (word == "connectControlClient"))) {
                line = removeSpace(line);
            }
            if (word.length() != 0) {
                command.push_back(word);
            }
        }
        if(command.size() > 0) {
            commandList.push_back(command);
        }
    }
    file.close();
    return commandList;
}

//parser
void Lexer :: parser(list<list<string>> commandList) {
    list<list<string>> :: iterator it = commandList.begin();
    while(it != commandList.end()) {
        string r = *it->begin();
        auto it2 = it->begin();
        it2++;
        if(r.compare("openDataServer") == 0){
            double port = I.interpret(*it2);
            //open server
            this->openServerCommand = new OpenServerCommand(port);
            openServerCommand->execute();
            //run with other thread and read info from sim
            thread* t1 = new thread(&OpenServerCommand::readFromSim, openServerCommand);
            m_thread_vector.push_back(t1);

        } else if(r.compare("connectControlClient")==0) {
            string ip = *it2;
            it2++;
            double portOfClient = I.interpret(*it2);
            // connected to sim server
            connectClientCommand = new ConnectClientCommand(ip, portOfClient);
            connectClientCommand->execute();
        } else if(r.compare("var") == 0) {
//            auto it2 = it->begin();
            string name = *(it2);
            it2++;
            string sign = *(it2);
            it2++;
            string numOfEqual = *(it2);
            if(sign == "->") {
                it2++;
                string path = *(it2);
                //create variable that send to sim value
                RightVar *rightVar = new RightVar(name, path, connectClientCommand);
                rightMap[name] = rightVar;
            }
            if(sign.compare("<-") ==0) {
                it2++;
                string path = *(it2);
                //create variable that get info from sim
                LeftVar* leftVar = new LeftVar(name,path);
                leftMap[name] = leftVar;
            }
            if(sign.compare("=") ==0) {
                double val = I.interpret(numOfEqual);
                cout <<val<<endl;
                // create variable that get value
                EqualVar* equalVar = new EqualVar(name, val);
                equalMap[name] = equalVar;
            }
        } else if(r.compare("Print") == 0) {
            if(rightMap.find(*it2) != rightMap.end()) {
                cout <<rightMap[*it2]->getVal()<< endl;
            }
            else if(leftMap.find(*it2)!= leftMap.end()) {
                cout <<leftMap[*it2]->getVal()<< endl;
            }
            else if(equalMap.find(*it2)!= equalMap.end()) {
                cout <<equalMap[*it2]->getVal()<< endl;
            }
            else if (I.getMap().find(*it2) != I.getMap().end()) {
                cout <<I.getMap()[*it2]<< endl;
            } else {
                string print = *it2;
                cout<<(print)<< endl;
            }
        } else if(r.compare("Sleep") == 0) {
            double d = I.interpret(*it2);
            int x = (int)d;
            //sleep that tread
            this_thread::sleep_for(std::chrono::milliseconds(x));
        } else if (r.compare("if") == 0 || r.compare("while") == 0) {
            string command = r;
            string left = *(it2);
            it2++;
            string sign = *(it2);
            it2++;
            string right = *it2;
            it++;
            list<list<string>> conditionList;
            int loop = 0;
            while (*(*it).begin() != "}" || loop) {
                if(*(*it).begin() == "while" || *(*it).begin() == "if") {
                    loop++;
                }
                if (*(*it).begin() == "}") {
                    loop--;
                }
                conditionList.push_back(*it);
                it++;
            }
            ConditionCommand* condition = new ConditionCommand(conditionList, command, left, sign, right);
            condition->execute();
        } else if(rightMap.find(r)!= rightMap.end()) {
            it2++;
            double d = I.interpret(*it2);
            //update value and update the sim
            rightMap[r]->setVal(d);
        } else if(equalMap.find(r)!= equalMap.end()) {
            it2++;
            double d = I.interpret(*it2);
            //update val
            equalMap[r]->setVal(d);
        } else if (funcMap.find(r)!= funcMap.end()) {
            list<string> num;
            while (it2 != (*it).end()) {
                num.push_back(*it2);
                it2++;
            }
            Function *f = funcMap[r];
            f->setVariables(num);
            f->execute();
        } else if ((I.getMap().find(r) != I.getMap().end())) {
            it2++;
            I.setMapValue(r, I.interpret(*it2));
        } else {
            // create function
            list<list<string>> conditionList;
            vector<string> vars;
            it2++;
            while (it2 != (*it).end()) {
                vars.push_back(*it2);
                it2++;
                if (it2 != (*it).end()){
                    it2++;
                }
            }
            it++;
            int condition = 0;
            while (*(*it).begin() != "}" || condition) {
                if (*(*it).begin() == "if" || *(*it).begin() == "while") {
                    condition++;
                }
                if (*(*it).begin() == "}") {
                    condition--;
                }
                conditionList.push_back(*it);
                it++;
            }
            Function* f = new Function(conditionList, vars);
            funcMap[r] = f;
        }
        it++;
    }
}
