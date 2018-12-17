//
// Created by oryakov on 12/16/18.
//

#ifndef MILESTONE1_PARSER_H
#define MILESTONE1_PARSER_H

#include <iostream>
#include <map>
#include <vector>
#include "Command.h"

using namespace std;

class Parser {
    map<string, Command*> stringCommandMap;
public:
    void parse(vector<string> lexedData);
};


#endif //MILESTONE1_PARSER_H
