//
// Created by oryakov on 12/17/18.
//

#include "ShuntingYard.h"

bool ShuntingYard::isOperator(char token) {
    for (auto &item: operators) {
        if (token == item) {
            return true;
        }
    }
    return false;
}

bool ShuntingYard::isOpenBracket(char token) {
    return (token == '(');
}

bool ShuntingYard::isCloseBracket(char token) {
    return (token == ')');
}

void ShuntingYard::initPriority() {
    priority.insert(pair<char, int>('/', 2));
    priority.insert(pair<char, int>('*', 2));
    priority.insert(pair<char, int>('+', 1));
    priority.insert(pair<char, int>('-', 1));
    priority.insert(pair<char, int>(')', 0));
    priority.insert(pair<char, int>('(', 0));
}

deque<string> ShuntingYard::makePostFixQueue(string &tokens) {
    initPriority();
    deque<string> resQueue;
    for (int i = 0; i < tokens.size(); ++i) {
        // if token is white space skip
        if (tokens[i] == ' ') {
            continue;
        }
            // if token is a digit
        else if (isdigit(tokens[i])) {
            string tempNum;
            // there could be several digits for a number and we want them all
            while (isdigit(tokens[i]) || (tokens[i] == '.')) {
                tempNum += tokens[i];
                ++i;
            }
            resQueue.push_back(tempNum);
            --i;
        } else if (isOperator(tokens[i])) {
            bool toPush = true;
            while (!opStack.empty()) {
                char topStack = opStack.top();
                int curTokenPrority = priority.at(tokens[i]);
                int topStackPriority = priority.at(topStack);
                if (topStackPriority >= curTokenPrority) {
                    string topStackString;
                    topStackString += topStack;
                    resQueue.push_back(topStackString);
                    opStack.pop();
                }
//                else if (topStackPriority == curTokenPrority) {
//                    char tempStackOp = opStack.top();
//                    opStack.pop();
//                    opStack.push(tokens[i]);
//                    opStack.push(tempStackOp);
//                    toPush = false;
//                    break;
//                }
                else {
                    break;
                }
            }
            opStack.push(tokens[i]);
        } else if (isOpenBracket(tokens[i])) {
            opStack.push((tokens[i]));
        } else if (isCloseBracket(tokens[i])) {
            while (!opStack.empty() && !(isOpenBracket(opStack.top()))) {
                string topStackString;
                topStackString += opStack.top();
                resQueue.push_back(topStackString);
                opStack.pop();
            }
            if (isOpenBracket(opStack.top())) {
                opStack.pop();
            }
        }
    }
    // push the remaining operators to queue
    while (!opStack.empty()) {
        string topStackString;
        topStackString += opStack.top();
        resQueue.push_back(topStackString);
        opStack.pop();
    }
    return resQueue;
}

bool ShuntingYard::isNumber(string token) {
    if (token[0] == '-') {
        token = token.erase(0, 1);
    }
    // check if it is a double or a float
    string str1 = ".";
    size_t found = token.find(str1);
    if (found != string::npos) {
        // erase the "."
        token = token.erase(found, (found + 1));
    }
    std::string::const_iterator it = token.begin();
    while (it != token.end() && std::isdigit(*it)) ++it;
    return !token.empty() && it == token.end();
}

Expression *ShuntingYard::createSimpleExp(char op, Expression *&leftExp,
                                          Expression *&rightExp) {
    switch (op) {
        case '+': {
            return new Plus(leftExp, rightExp);
        }
        case '-': {
            return new Minus(leftExp, rightExp);
        }
        case '*': {
            return new Mul(leftExp, rightExp);
        }
        case '/': {
            return new Div(leftExp, rightExp);
        }
    }
}

// Function to reverse the queue
void reverseQueue(deque<string> &Queue) {
    stack<string> Stack;
    while (!Queue.empty()) {
        Stack.push(Queue.front());
        Queue.pop_front();
    }
    while (!Stack.empty()) {
        Queue.push_back(Stack.top());
        Stack.pop();
    }
}

Expression *ShuntingYard::evaluateExpression(string tokens) {
    deque<string> preFixQueue = makePostFixQueue(tokens);
    reverseQueue(preFixQueue);
    Expression* resExp = fullyCalculate(preFixQueue);
    return resExp;
}

bool ShuntingYard::isNextNeg(deque<string> &preFixQueue, stack<char> &opStack) {
    bool res = false;
    if (!opStack.empty()) {
        string next1, next2, next3;
        vector<string> nextObjects = {next1, next2, next3};
        int j = 0;
        while (!preFixQueue.empty()) {
            nextObjects[j] = preFixQueue.front();
            preFixQueue.pop_front();
            ++j;
        }
        if (isNumber(nextObjects[0]) && isNumber(nextObjects[1])) {
            if (nextObjects[2].empty() || !isNumber(nextObjects[2])) {
            //next1 is negative
            res = true;
            }
        }
        int k = 2;
        while (k >= 0) {
            preFixQueue.push_front(nextObjects[k]);
            --k;
        }
    }
    return res;
}

Expression *ShuntingYard::fullyCalculate(deque<string> &preFixQueue) {
    int counter = 0;
    stack<Expression *> expStack;
    stack<char> opStack;
    string token;
    while (!preFixQueue.empty()) {
        token = preFixQueue.front();
        preFixQueue.pop_front();
        // we defined the token as string but operator is char, but in any case - if it's an operator it's a char
        // and if it's a char it's the same as string[0].
        if (isOperator(token[0]) && (token.size() == 1)) {
            // special case for negative number
            if (token[0] == '-') {
                if (isNextNeg(preFixQueue, opStack)) {
                    string negNum = preFixQueue.front();
                    preFixQueue.pop_front();
                    negNum = '-' + negNum;
                    preFixQueue.push_front(negNum);
                    continue;
                }
            }

            // pop the next two items
            string second = preFixQueue.front();
            preFixQueue.pop_front();
            string first = preFixQueue.front();
            preFixQueue.pop_front();
            if (isNumber(first) && isNumber(second)) {
                Expression *leftExp = new Num(stod(first));
                Expression *rightExp = new Num(stod(second));
                expStack.push(createSimpleExp(token[0], leftExp, rightExp));
                ++counter;
                whichStack[counter] = EXP;
            } else {
                opStack.push(token[0]);
                preFixQueue.push_front(first);
                preFixQueue.push_front(second);
                ++counter;
                whichStack[counter] = OP;
            }
        } else if (isNumber(token)) {
            Expression *num = new Num(stod(token));
            expStack.push(num);
            ++counter;
            whichStack[counter] = EXP;
//            if (expStack.size() == 2) {///
//                Expression *leftExp = expStack.top();
//                expStack.pop();
//                Expression *rightExp = expStack.top();
//                expStack.pop();
//                char op = opStack.top();
//                opStack.pop();
//                expStack.push(createSimpleExp(op, leftExp, rightExp));
//            }
        }
    }
    if (!opStack.empty()) {
        for (int a = counter; a > 0; --a) {
            if (whichStack.at(a) == EXP) {
                preFixQueue.push_front(to_string(expStack.top()->calculate()));
                expStack.pop();
            } else if (whichStack.at(a) == OP) {
                string topStackString;
                topStackString += opStack.top();
                preFixQueue.push_front(topStackString);
                opStack.pop();
            }
        }


//        while (!expStack.empty()) {
//            preFixQueue.push_front(to_string(expStack.top()->calculate()));
//            expStack.pop();
//        }
//        while (!opStack.empty()) {
//            string topStackString;
//            topStackString += opStack.top();
//            preFixQueue.push_front(topStackString);
//            opStack.pop();
//        }
    whichStack.clear();
    return fullyCalculate(preFixQueue);
    }

//    while (!opStack.empty()) {
//        char op = opStack.top();
//        opStack.pop();
//        Expression *leftExp = expStack.top();
//        expStack.pop();
//        Expression *rightExp = expStack.top();
//        expStack.pop();
//        expStack.push(createSimpleExp(op, leftExp, rightExp));
//    }
    return expStack.top();
}










