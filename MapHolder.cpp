//
// Created by oryakov on 12/20/18.
//

#include "MapHolder.h"

MapHolder *MapHolder::instance = nullptr;

MapHolder *MapHolder::getInstance() {
    if (instance == nullptr) {
        instance = new MapHolder;
    }
    return instance;
}

const map<string, double>& MapHolder::getSymbolTable() const {
    return symbolTable;
}

void MapHolder::setSymbolTable(const map<string, double> &symbolTable) {
    MapHolder::symbolTable = symbolTable;
}

const map<string, double> &MapHolder::getPathAndValueMap() const {
    return pathAndValueMap;
}

void MapHolder::setPathAndValueMap(const map<string, double> &pathAndValueMap) {
    MapHolder::pathAndValueMap = pathAndValueMap;
}

const map<string, string> &MapHolder::getVarAndPathMap() const {
    return varAndPathMap;
}

void MapHolder::setVarAndPathMap(const map<string, string> &varAndPathMap) {
    MapHolder::varAndPathMap = varAndPathMap;
}

double MapHolder::getValueByVar(string var) {
    return symbolTable.at(var);
}

double MapHolder::getValueByPath(string path) {
    return pathAndValueMap.at(path);
}

string MapHolder::getPathByVar(string var) {
    return varAndPathMap.at(var);
}

void MapHolder::setVarValue(string var, double value) {
    lock_guard<mutex> g(mutex1);
    symbolTable[var] = value;
    //cout << var + " "; cout << value<<endl;
    for (int i = 0; i < vars.size(); ++i) {
        if (vars[i] == var) {
            return;
        }
    }
    vars.push_back(var);

}

void MapHolder::setPathValue(string path, double value) {
    lock_guard<mutex> g(mutex1);
    if (!pathAndValueMap.count(path) || pathAndValueMap.empty()) {
        pathAndValueMap.insert(pair<string, double>(path, value));
        return;
    }
    pathAndValueMap[path] = value;
}

void MapHolder::setVarPath(string var, string path) {
    lock_guard<mutex> g(mutex1);
    varAndPathMap[var] = path;
    vars.push_back(var);
}

const vector<string> &MapHolder::getVars() const {
    return vars;
}

MapHolder::MapHolder() {

}

int MapHolder::getSockfd() const {
    return sockfd;
}

void MapHolder::setSockfd(int sockfd) {
    MapHolder::sockfd = sockfd;
}

bool MapHolder::isStopThreadLoop() const {
    return stopThreadLoop;
}

void MapHolder::setStopThreadLoop(bool stopThreadLoop) {
    MapHolder::stopThreadLoop = stopThreadLoop;
}

thread *MapHolder::getServerThread() const {
    return serverThread;
}

void MapHolder::setServerThread(thread *serverThread) {
    MapHolder::serverThread = serverThread;
}
