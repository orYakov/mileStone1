//
// Created by oryakov on 12/20/18.
//

#include <unistd.h>
#include "SleepCommand.h"

int SleepCommand::doCommand(vector<string> commandOperation) {
    int microSec = stoi(commandOperation[0]);
    int miliSec = microSec * 1000;
    usleep(miliSec);
}
