//
// Created by oryakov on 12/17/18.
//

#include "ShuntingYard.h"

bool ShuntingYard::isnumber(string token) {
        std::string::const_iterator it = token.begin();
        while (it != token.end() && std::isdigit(*it)) ++it;
        return !token.empty() && it == token.end();

}

bool ShuntingYard::isOperator(string token) {
    for (auto &item: operators) {
        if (token == item) {
            return true;
        }
    }
    return false;
}

bool ShuntingYard::isOpenBracket(string token) {
    return (token == "(");
}

bool ShuntingYard::isCloseBracket(string token) {
    return (token == ")");
}
