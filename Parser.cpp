
#include "Parser.h"
#include "OpenServerCommand.h"
#include "DefineVarCommand.h"
#include "PrintCommand.h"
#include "ConditionParser.h"
#include "LoopCommand.h"
#include "IfCommand.h"
#include "DefinitionCommand.h"
#include "SleepCommand.h"
#include "ConnectCommand.h"

using namespace std;

Parser::Parser(vector<string> commandsList) {
    commands = commandsList;
    index = 0;
    stringCommandMap.insert(pair<string, Command*>("openDataServer",new OpenServerCommand));
    stringCommandMap.insert(pair<string, Command*>("connect",new ConnectCommand));
    stringCommandMap.insert(pair<string, Command*>("var", new DefineVarCommand));
    stringCommandMap.insert(pair<string, Command*>("print", new PrintCommand));
    stringCommandMap.insert(pair<string, Command*>("sleep", new SleepCommand));
}


void Parser::callCondition() {
    int bracketCounter = 0;
    vector<string> allConCom;
    bool haveOneCon = false;
    int i = index;
    for (i; i< commands.size(); i++){
        if(commands[i] == "{" ){
            bracketCounter++;
            haveOneCon = true;
        }else if(commands[i] == "}" ) {
            bracketCounter--;
        }
        if(bracketCounter == 0 && haveOneCon == true){
            break;
        }
        //not send last "}"
        allConCom.push_back(commands[i]);
    }

    this->index = i + 2;
    if (allConCom[0] == "while") {
        LoopCommand* loopCommand = new LoopCommand;
        loopCommand->doCommand(allConCom, index);
        delete loopCommand;
    } else if (allConCom[0] == "if") {
        IfCommand* ifCommand = new IfCommand;
        ifCommand->doCommand(allConCom, index);
        delete ifCommand;
    }
    //ConditionParser* conParser = new ConditionParser(allConCom);
    //conParser->conImp();
    //delete (conParser);
}

void Parser::parse() {

    while (index <= commands.size()-1) {
        Command *c;
        if (stringCommandMap.count(commands[index]) == 0) {
            c = NULL;
        } else {
            c = stringCommandMap.find(commands[index])->second;
        }

        if (c != NULL) {
            index += c->doCommand(commands, index);
            //   delete (c); - not good!
        } else if (c == NULL) {
            mutex mutex1;
            mutex1.lock();
            map<string, double> symbolTableCopy = mapHolder->getSymbolTable();
            mutex1.unlock();
            if (symbolTableCopy.count(commands[index])) {
                c = new DefinitionCommand; // symbol without var //
                index += c->doCommand(commands, index);
                delete (c);
            } else if (commands.at(index) == "if" || commands.at(index) == "while") {
                callCondition();
            }
        }
    }
    index = 0;
}

int Parser::getReturnIndex(vector<string> commandOperation, int index) {
    int resIndex = index;
    // set the index to return
    while (commandOperation[resIndex] != "@") {
        ++resIndex;
    }
    resIndex++; // skip the "@"
    resIndex -= index;
    return resIndex;
}

///