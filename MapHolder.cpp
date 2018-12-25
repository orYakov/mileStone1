//
// Created by oryakov on 12/20/18.
//

#include "MapHolder.h"
MapHolder* MapHolder::instance = nullptr;

 MapHolder *MapHolder::getInstance() {
    if (instance == nullptr) {
        instance = new MapHolder;
    }
    return instance;
}

const map<string, double> &MapHolder::getSymbolTable() const {
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
    symbolTable[var] = value;
    for (int i = 0; i< vars.size(); ++i) {
        if (vars[i] == var){
            return;
        }
    }
    vars.push_back(var);
}

void MapHolder::setPathValue(string path, double value) {
    pathAndValueMap[path] = value;
}

void MapHolder::setVarPath(string var, string path) {
    varAndPathMap[var] = path;
    vars.push_back(var);
}

const vector<string> &MapHolder::getVars() const {
    return vars;
}

MapHolder::MapHolder() {

}
////