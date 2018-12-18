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

deque<string> ShuntingYard::makePostFixQueue(string tokens) {
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
            while (isdigit(tokens[i])) {
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
    stack<Expression *> expStack;
    stack<char> opStack;
    string token;
    while (!preFixQueue.empty()) {
        token = preFixQueue.front();
        preFixQueue.pop_front();
        // we defined the token as string but operator is char, but in any case - if it's an operator it's a char
        // and if it's a char it's the same as string[0].
        if (isOperator(token[0])) {
            // pop the next two items
            string second = preFixQueue.front();
            preFixQueue.pop_front();
            string first = preFixQueue.front();
            preFixQueue.pop_front();
            if (isNumber(first) && isNumber(second)) {
                Expression *leftExp = new Num(stoi(first));
                Expression *rightExp = new Num(stoi(second));
                expStack.push(createSimpleExp(token[0], leftExp, rightExp));
            }
            else {
                opStack.push(token[0]);
                preFixQueue.push_front(first);
                preFixQueue.push_front(second);
            }
        }
        else if (isNumber(token)) {
            Expression *num = new Num(stoi(token));
            expStack.push(num);
//            if (expStack.size() == 2) {
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
    while (!opStack.empty()) {
        char op = opStack.top();
        opStack.pop();
        Expression *leftExp = expStack.top();
        expStack.pop();
        Expression *rightExp = expStack.top();
        expStack.pop();
        expStack.push(createSimpleExp(op, leftExp, rightExp));
    }
    return expStack.top();
}







