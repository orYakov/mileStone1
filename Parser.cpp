//
// Created by oryakov on 12/16/18.
//

#include "Parser.h"

void Parser::parse(vector<string> lexedData) {
    for (int i = 0; i < lexedData.size(); ++i) {
        Command* c = stringCommandMap.at(lexedData[i]);
        if (c != NULL) {
            c->doCommand(lexedData[i]);
        }
    }
}
