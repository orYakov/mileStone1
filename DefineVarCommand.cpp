//
// Created by oryakov on 12/20/18.
//

#include "DefineVarCommand.h"

DefineVarCommand::DefineVarCommand() {
    initSymbolTable();
}

void DefineVarCommand::initSymbolTable() {
    symbolTable.insert(pair<string, double >("breaks", 0));
    symbolTable.insert(pair<string, double >("throttle", 0));
    symbolTable.insert(pair<string, double >("heading", 0));
    symbolTable.insert(pair<string, double >("airspeed", 0));
    symbolTable.insert(pair<string, double >("roll", 0));
    symbolTable.insert(pair<string, double >("pitch", 0));
    symbolTable.insert(pair<string, double >("rudder", 0));
    symbolTable.insert(pair<string, double >("aileron", 0));
    symbolTable.insert(pair<string, double >("elevator", 0));
    symbolTable.insert(pair<string, double >("alt", 0));
}

