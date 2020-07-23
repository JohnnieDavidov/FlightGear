//
// Created by zvi on 04/11/2019.
//

#ifndef FLIGHTGEAR_INTERPRETER_H
#define FLIGHTGEAR_INTERPRETER_H

#include <iostream>
#include <iterator>
#include <map>
#include <queue>

#include "Expression.h"

class Value: public Expression {
    double val;
public:
    Value(double num);
    double calculate();
    //virtual ~Value();
};

class Variable: public Expression {
    string var;
    double val;
public:
    Variable(string name, double num);
    double calculate();
    //virtual ~Variable();
    Variable& operator ++();
    Variable& operator ++(int);
    Variable& operator +=(double num);
    Variable& operator --();
    Variable& operator --(int);
    Variable& operator -=(double num);
};

class UnaryOperator: public Expression {
protected:
    Expression* v;
};

class UPlus: public UnaryOperator {
public:
    UPlus(Expression* val);
    double calculate();
    //virtual ~UPlus();
};

class UMinus: public UnaryOperator {
public:
    UMinus(Expression* val);
    double calculate();
    //virtual ~UMinus();
};

class BinaryOperator: public Expression {
protected:
    Expression* e1;
    Expression* e2;
};

class Plus : public BinaryOperator {
public:
    Plus(Expression* ex1, Expression* ex2);
    double calculate();
    //virtual ~Plus();
};

class Minus: public BinaryOperator {
public:
    Minus(Expression* ex1, Expression* ex2);
    double calculate();
    //virtual ~Minus();
};

class Mul: public BinaryOperator {
public:
    Mul(Expression* ex1, Expression* ex2);
    double calculate();
    //virtual ~Mul();
};

class Div: public BinaryOperator {
public:
    Div(Expression* ex1, Expression* ex2);
    double calculate();
    //virtual ~Div();
};

//interpreter
class Interpreter {
    unordered_map<string,double> variable;
public:
    Interpreter();
    double interpret(string str);
    void setVariables(vector<string> vars, list<string> num);
    double stod(string s);
    queue<string> shoutingYard(string str);
    unordered_map<string,double> getMap();
    void setMapValue(string var, double num);
};


#endif //UNTITLED1_INTERPRETER_H
