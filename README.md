# Flightgear Simulation
This program created in Advance Programing course in Bar-Ilan University 2020.

crated by Zvi Arie Berger and Yonatan Davidov.

## Creators
Zvi Arie Berger

- **I.D** : 206126575
- **Submit name** : zviarib

Yonatan Davidov

- **I.D** : 308447234
- **Submit name** : davidoy5

## Intrudoction
The project Written on clion in c++. We work together on the project and 
we lerrn a lot about how to use server and client connection.


## Description
The project connect to the simulator and fly the airplan with 
the commands in fly.txt file. We lexer and parser the commands in the file
and send a values to the simulators. also we getting values from the simulator
and update our data.

we use maps to get a value in o(1). the keys of the maps are the vars name or
the path of the values. all the maps are global in order to recognize in all class
in the project.

we also used thread that listening to the simulator and update our maps.

Our project can run also Function with number parameter or variables parameter.

we also supprted a while loop and if condition even if there is loop in loop
or function in loop.


## Run Project
- download Flight gear simulator (link in below).
- write in flight simulator advanced settings: 

`--telnet=socket,in,10,10.0.2,5402,tcp `

`--generic=socket,out,10,127.0.1,5400,tcp,generic_small`

- compile in terminal (on linux) with command:

`g++ -std=c++11 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread`

- run the out file with command:

`a.out fly.txt`
- press fly on flght simulator.

## Files
- main.c 

### command file
- Command.h
- ConnectClientCommand.h
- ConnectClientCommand.cpp
- OpenServerCommand.h
- OpenServerCommand.cpp
- ConditionCommand.h
- ConditionCommand.cpp
- Function.h
- Function.cpp

### variables files
- EqualVar.h
- EqualVar.cpp
- LeftVar.h
- LeftVar.cpp
- RightVar.h
- RightVar.cpp
- Expression.h

### Function class
- Lexer.h
- Lexer.cpp
- Interpreter.h
- Interpreter.cpp

### Txt Files
- fly.txt
- fly_with_func.txt

## Links
- Our GitHub project https://github.com/JohnnieDavidov/FlightGear
- Download FlightGear Simulator https://www.flightgear.org/download/
