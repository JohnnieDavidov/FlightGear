//
// Created by johnnie on 22/12/2019.
//

#include <cstring>
#include "OpenServerCommand.h"
#include "LeftVar.h"

std::mutex mtx;
extern unordered_map<string, LeftVar*> leftMap;

//constructor
OpenServerCommand::OpenServerCommand(double port) : m_port(port) {}

int OpenServerCommand::execute() {

    m_socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socketFd == -1) {
        //error
        cerr<<"could not create a socket"<<endl;
        return -1;
    }
    //bind socket to IP address
    //we first create the sockaddr obj.
    sockaddr_in address;//in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");//give me any IP allocated for my machine.
    //address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(m_port);
    //we need to convert our number
    //to a number that the network understands

    //the actual bind command
    if (bind(m_socketFd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        cerr<<"could not bind socket to an IP"<<endl;
        return -1;
    }

    if (listen(m_socketFd, 1) == -1) {
        cerr<<"Error during listening command"<<endl;
    }
    int addrlen = sizeof(address);
    int client_socket = accept(m_socketFd, (struct sockaddr *) &address, (socklen_t*)&addrlen);

    if (client_socket == -1) {
        cerr<<"Error accepting"<<endl;
        return -1;
    }
    m_fd = client_socket;
    connected = true;
    return 1;
}

void OpenServerCommand::getInfoAboutSim() {
    auto it = leftMap.begin();
    while (it!= leftMap.end()) {
         double d = m_map[it->second->getPath()];
        it->second->setVal(d);
        it++;
    }
}

/*
 * reading a line of 36 values seprated by comma from the simulater every 10 secondes.
 * this method should run as long as there is a connection.
 */
int OpenServerCommand::readFromSim() {
    int valread = 0;
    while(valread != -1 && connected) {
        mtx.lock();
        char buffer[100000] = {0};
        valread = read(m_fd, buffer, 10000);
        //insert to the map of path
        insertBufferToMap(buffer, strlen(buffer));
        //update the map of leftVar from buffer
        getInfoAboutSim();
        mtx.unlock();
    }
    closeServer();
    return 0;
}

/*
 * param the line from the simulator of 36 values.
 * the method puts all the values in m_array in order.
 * then transfer it to unordered_map according to the order
 * specified in the generic_small.xml.
 */
int OpenServerCommand::insertBufferToMap(char *buffer, int buffer_len) {
    int array_index = 0;
    //stores a singel value from the line.
    string val = "";
    //going over the line
    for (int i = 0; i < buffer_len; i++) {
        if (buffer[i] == ',') {
            m_array[array_index] = atof(val.c_str());
            val = "";
            array_index++;
            continue;
        }
        val = val + buffer[i];
    }
    m_array[array_index] = atof(val.c_str());

    m_map["/instrumentation/airspeed-indicator/indicated-speed-kt"] = m_array[0];
    m_map["/sim/time/warp"] = m_array[1];
    m_map["/controls/switches/magnetos"] = m_array[2];
    m_map["/instrumentation/heading-indicator/offset-deg"] = m_array[3];
    m_map["/instrumentation/altimeter/indicated-altitude-ft"] = m_array[4];
    m_map["/instrumentation/altimeter/pressure-alt-ft"] = m_array[5];
    m_map["/instrumentation/attitude-indicator/indicated-pitch-deg"] = m_array[6];
    m_map["/instrumentation/attitude-indicator/indicated-roll-deg"] = m_array[7];
    m_map["/instrumentation/attitude-indicator/internal-pitch-deg"] = m_array[8];;
    m_map["/instrumentation/attitude-indicator/internal-roll-deg"] = m_array[9];;
    m_map["/instrumentation/encoder/indicated-altitude-ft"] = m_array[10];;
    m_map["/instrumentation/encoder/pressure-alt-ft"] = m_array[11];;
    m_map["/instrumentation/gps/indicated-altitude-ft"] = m_array[12];;
    m_map["/instrumentation/gps/indicated-ground-speed-kt"] = m_array[13];;
    m_map["/instrumentation/gps/indicated-vertical-speed"] = m_array[14];
    m_map["/instrumentation/heading-indicator/indicated-heading-deg"] = m_array[15];;
    m_map["/instrumentation/magnetic-compass/indicated-heading-deg"] = m_array[16];;
    m_map["/instrumentation/slip-skid-ball/indicated-slip-skid"] = m_array[17];
    m_map["/instrumentation/turn-indicator/indicated-turn-rate"] = m_array[18];
    m_map["/instrumentation/vertical-speed-indicator/indicated-speed-fpm"] = m_array[19];
    m_map["/controls/flight/aileron"] = m_array[20];
    m_map["/controls/flight/elevator"] = m_array[21];
    m_map["/controls/flight/rudder"] = m_array[22];
    m_map["/controls/flight/flaps"] = m_array[23];
    m_map["/controls/engines/engine/throttle"] = m_array[24];
    m_map["/controls/engines/current-engine/throttle"] = m_array[25];
    m_map["/controls/switches/master-avionics"] = m_array[26];
    m_map["/controls/switches/starter"] = m_array[27];
    m_map["/engines/active-engine/auto-start"] = m_array[28];
    m_map["/controls/flight/speedbrake"] = m_array[29];
    m_map["/sim/model/c172p/brake-parking"] = m_array[30];
    m_map["/controls/engines/engine/primer"] = m_array[31];
    m_map["/controls/engines/current-engine/mixture"] = m_array[32];
    m_map["/controls/switches/master-bat"] = m_array[33];
    m_map["/controls/switches/master-alt"] = m_array[34];
    m_map["/engines/engine/rpm"] = m_array[35];

    return 0;
}
//close the server
void OpenServerCommand::closeServer() {
    close(m_fd);
    close(m_socketFd);
}




