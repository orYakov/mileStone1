//
// Created by oryakov on 12/20/18.
//

#ifndef MILESTONE1_MAPHOLDER_H
#define MILESTONE1_MAPHOLDER_H
#include <iostream>
#include <map>
#include <vector>
#include <mutex>
#include <thread>

using namespace std;

class MapHolder {
    static MapHolder* instance;
    map<string, double> symbolTable;
    map<string, double> pathAndValueMap;
    map<string, string> varAndPathMap;
    //string breaks, throttle, heading, airspeed, roll, pitch, rudder, aileron, elevator, alt, h0;
    vector<string> vars;
    //mutex mutex1;
    int sockfd = 0;
    bool stopThreadLoop = false;
    thread* serverThread;
public:
    thread *getServerThread() const;

    void setServerThread(thread *serverThread);

private:

    // Private constructor so that no objects can be created.
    MapHolder();

public:
    static MapHolder* getInstance();

    const map<string, double> &getSymbolTable() const;

    void setSymbolTable(const map<string, double> &symbolTable);

    const map<string, double> &getPathAndValueMap() const;

    void setPathAndValueMap(const map<string, double> &pathAndValueMap);

    const map<string, string> &getVarAndPathMap() const;

    void setVarAndPathMap(const map<string, string> &varAndPathMap);

    double getValueByVar (string var);

    double getValueByPath (string path);

    string getPathByVar (string var);

    void setVarValue(string var, double value);

    void setPathValue(string path, double value);

    void setVarPath(string var, string path);

    const vector<string> &getVars() const;

    int getSockfd() const;

    void setSockfd(int sockfd);

    bool isStopThreadLoop() const;

    void setStopThreadLoop(bool stopThreadLoop);
};


#endif //MILESTONE1_MAPHOLDER_H
///