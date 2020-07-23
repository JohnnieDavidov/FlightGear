//
// Created by zvi on 04/11/2019.
//
#include <string>
#include <queue>
#include <stack>
#include <unordered_map>
#include <list>

#include "Interpreter.h"
#include "Expression.h"
#include "RightVar.h"
#include "LeftVar.h"
#include "EqualVar.h"

//global data
extern unordered_map<string, RightVar*> rightMap;
extern unordered_map<string, LeftVar*> leftMap;
extern unordered_map<string, EqualVar*> equalMap;

//value function
Value :: Value(double num) {
    val = num;
}
double Value :: calculate() {
    return val;
}

// variable function
Variable :: Variable(string x, double num) {
    var = x;
    val = num;
}
double Variable :: calculate() {
    return val;
}
// overloading operator
// plus function
Variable& Variable :: operator ++() {
    val = val + 1;
    return *this;
}
Variable& Variable :: operator ++(int) {
    val = val + 1;
    return *this;
}
Variable& Variable :: operator +=(double num) {
    val = val + num;
    return *this;
}
// minus function
Variable& Variable :: operator --() {
    val = val - 1;
    return *this;
}
Variable& Variable :: operator --(int) {
    val = val -1;
    return *this;
}
Variable& Variable :: operator -=(double num) {
    val = val - num;
    return *this;
}

// unary expression
UPlus :: UPlus(Expression* val)
{
    v = val;
}
double UPlus :: calculate() {
    return v->calculate();
}

UMinus :: UMinus(Expression* val)
{
    v = val;
}
double UMinus :: calculate() {
    return (-1) * v->calculate();
}

// binary expression
Plus :: Plus(Expression* ex1, Expression* ex2)
{
    e1 = ex1;
    e2 = ex2;
}
double Plus :: calculate()
{
    return e1->calculate() + e2->calculate();
}


Minus :: Minus(Expression* ex1, Expression* ex2)
{
    e1 = ex1;
    e2 = ex2;
}
double Minus:: calculate()
{
    return e1->calculate() - e2->calculate();
}

Mul :: Mul(Expression* ex1, Expression* ex2)
{
    e1 = ex1;
    e2 = ex2;
}
double Mul:: calculate()
{
    return e1->calculate() * e2->calculate();
}


Div :: Div(Expression* ex1, Expression* ex2)
{
    e1 = ex1;
    e2 = ex2;
    if (e2->calculate() == 0) {
        throw "Error: Divid by zero";
    }
}
double Div :: calculate()
{
    return e1->calculate() / e2->calculate();
}

//interpreter function
Interpreter :: Interpreter() {}

//check precede operator
bool isprecede(char str, char top) {
    if (((str == '*') || (str == '/')) && ((top == '*') || (top == '/'))) {
        return true;
    }
    if (((str == '-') || (str == '+'))) {
        return true;
    }
    //$ # unary expression of + -
    if ((top == '#') || (top == '$')) {
        return true;
    }
    return false;
}

bool isoperator(char c) {
    //$ # unary expression of + -
    if ((c == '*') || (c == '/') || (c == '+') || (c == '-') || (c == '#') || (c == '$')) {
        return true;
    }
    return false;
}
bool isoperator(string s) {
    if ((s == "*") || (s == "/") || (s == "+") || (s == "-") || (s == "#") || (s == "$")) {
        return true;
    }
    return false;
}
bool isdouble(string s) {
    for (unsigned int i = 0; i < s.length(); i++) {
        if ((s[i] != '.') && (!isdigit(s[i]))) {
            return false;
        }
    }
    return true;
}
bool isletter(char c) {
    if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))) {
        return true;
    }
    return false;
}

bool isvariale(string v) {
    for(unsigned int i = 0; i < v.length(); i++) {
        if ((v[i] != '_') && (!isdigit(v[i])) && (!isletter(v[i]))) {
            return false;
        }
    }
    return true;
}

//convert string to double number.
double Interpreter :: stod(string s) {
    int length = s.length();
    int point = 0;
    int power = 0;
    double sum = 0;
    double tmp = 0;
    // begin pass on the string
    for (int i = 0; i < length; i++) {
        if (s[i] == '.') {
            point = 1;
        } else if (isdigit(s[i])) {
            if (point == 0) {
                sum = (sum * 10) + (s[i] - '0'); // askii value of '0' is 48
            } else {
                power++;
                tmp = s[i] - '0';
                for (int j = 0; j < power; j++) {
                    tmp = tmp / 10.0;
                }
                sum = sum + tmp;
            }
        } else {
            cout << "Eror: No Valid String!";
        }
    }
    return sum;
}

//convert char to string
string ctos(char c) {
    switch (c){
        case '*': return "*";
        case '/': return "/";
        case '+': return "+";
        case '-': return "-";
        case '#': return "#";
        case '$': return "$";
    }
    return 0;
}

// return map
unordered_map<string,double> Interpreter :: getMap() {
    return this->variable;
}

//set value in map
void Interpreter:: setMapValue(string var, double num){
    this->variable[var] = num;
}


//insert variables and values into the map.
void Interpreter :: setVariables(vector<string> vars, list<string> num) {
    list<string> :: iterator it = num.begin();
    for (auto var = vars.begin(); var != vars.end(); var++) {
        it++;
        it++;
        this->variable[*var] = this->interpret(*it);
    }
}

//shouting yard algorithm.
queue<string>  Interpreter :: shoutingYard(string str) {
    queue<string> output;
    stack<char> op;
    for(unsigned int i = 0; i < str.length(); i++) {
        // check if number.
        if ((str[i] - '0' >= 0) && (str[i] - '0' <= 9)) {
            string temp = "";
            while (((i < str.length()) && (isdigit(str[i]))) || (str[i] == '.')) {
                temp = temp + str[i];
                i++;
            }
            output.push(temp);
            i--;
            continue;
        } else if ((str[i] == '+') || (str[i] == '-')) { // change unary function, + to p, - to m.
            if (((i >= 1) && (str[i-1] == '(')) || (i == 0)) {
                if (str[i] == '-') {
                    op.push('#');
                }
                if (str[i] == '+') {
                    op.push('$');
                }
                continue;
            }
        }
        if (isoperator(str[i])) { // check if binary operation
            if(((i < str.length()) && isoperator(str[i+1]))  || (i == str.length())) {
                throw ("Error: Bad Input");
            }
            while ((!op.empty()) && (isprecede(str[i], op.top())) && (op.top() != '(')) {
                output.push(ctos(op.top()));
                op.pop();
            }
            op.push(str[i]);
        } else if (str[i] == '(') {  // check if parenthsis.
            op.push(str[i]);
        } else if (str[i] == ')') {
            while ((!op.empty()) && (op.top() != '(')) {
                output.push(ctos(op.top()));
                op.pop();
            }
            if ((!op.empty()) && (op.top() == '(')) {
                op.pop();
            } else {
                string temp = "";
                while (i < str.length() && (!isoperator(str[i]))) {
                    temp += str[i];
                    i++;
                }
                output.push(temp);
            }
        } else { // insert variable
            string temp = "";
            while ((!isoperator(str[i])) && (str[i] != ')') && (i < str.length())) {
               temp += str[i];
               i++;
            }
            if (isvariale(temp)) {
                output.push(temp);
            } else {
                throw ("Eror: Bad Input");
            }
            i--;
        }
    }
    while (!op.empty()) {
        output.push(ctos(op.top()));
        op.pop();
    }
    return output;
}

//convert string to expression.
double Interpreter :: interpret(string str) {
    stack<Expression*> ex;
    if (equalMap.find(str) != equalMap.end()) {
        return equalMap[str]->getVal();
    } else if (leftMap.find(str) != leftMap.end()) {
        return leftMap[str]->getVal();
    } else if (rightMap.find(str) != rightMap.end()) {
        return rightMap[str]->getVal();
    } else if (variable.find(str) != variable.end()) {
        return variable[str];
    }
    queue<string> postfix = shoutingYard(str);
    while (!postfix.empty()) {
        if (isdouble(postfix.front())) {
            ex.push(new Value(stod(postfix.front())));
        } else if (isoperator(postfix.front()) && (!ex.empty())) {
            Expression* tmp1;
            Expression* tmp2;
            //$ # unary expression of + -
            if (postfix.front() == "#") {
                tmp1 = new UMinus (ex.top());
                ex.pop();
                ex.push(tmp1);
            } else if (postfix.front() == "$") {
                tmp1 = new UPlus (ex.top());
                ex.pop();
                ex.push(tmp1);
            } else if (postfix.front() == "+") {
                tmp1 = ex.top();
                ex.pop();
                if (!ex.empty()) {
                    tmp2 = ex.top();
                    ex.pop();
                    ex.push(new Plus(tmp2, tmp1));
                }
            } else if (postfix.front() == "-") {
                tmp1 = ex.top();
                ex.pop();
                if (!ex.empty()) {
                    tmp2 = ex.top();
                    ex.pop();
                    ex.push(new Minus(tmp2, tmp1));
                }
            } else if (postfix.front() == "*") {
                tmp1 = ex.top();
                ex.pop();
                if (!ex.empty()) {
                    tmp2 = ex.top();
                    ex.pop();
                    ex.push(new Mul(tmp2, tmp1));
                }
            } else if (postfix.front() == "/") {
                tmp1 = ex.top();
                ex.pop();
                if (!ex.empty()) {
                    tmp2 = ex.top();
                    ex.pop();
                    ex.push(new Div(tmp2, tmp1));
                }
            }
        } else if (isvariale(postfix.front())) { // this is a variable.
            double val;
            if (equalMap.find(postfix.front()) != equalMap.end()) {
                val = equalMap[postfix.front()]->getVal();
            } else if (leftMap.find(postfix.front()) != leftMap.end()) {
                val = leftMap[postfix.front()]->getVal();
            } else if (rightMap.find(postfix.front()) != rightMap.end()) {
                val = rightMap[postfix.front()]->getVal();
            } else if (variable.find(postfix.front()) != variable.end()) {
                val = variable[postfix.front()];
            } else {
                return 0;
            }
            ex.push(new Variable(postfix.front(), val));
        } else if (ex.empty()) {
            return 0;
        }
        postfix.pop();
    }
    return ex.top()->calculate();
}

