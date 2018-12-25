//
// Created by oryakov on 12/20/18.
//

#include <unistd.h>
#include "SleepCommand.h"
#include "Parser.h"

int SleepCommand::doCommand(vector<string> commandOperation, int index) {
    int resIndex = Parser::getReturnIndex(commandOperation, index);
    int microSec = stoi(commandOperation[index + 1]);
    int miliSec = microSec * 1000;
    usleep(miliSec);

    return resIndex;
}
///