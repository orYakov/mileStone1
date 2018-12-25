//
// Created by oryakov on 12/16/18.
//

#ifndef MILESTONE1_PARSER_H
#define MILESTONE1_PARSER_H

#include <iostream>
#include <map>
#include <vector>
#include "Command.h"
#include "MapHolder.h"

using namespace std;

class Parser {
    map<string, Command*> stringCommandMap;
    MapHolder* mapHolder = MapHolder::getInstance();
    vector<string> commands;
    int index;
public:
    Parser(vector<string> commandsList);
    //void parse(vector<string> lexedData);
    void parse();
    void callCondition();
    static int getReturnIndex(vector<string> commandOperation, int index);
};


#endif //MILESTONE1_PARSER_H
///