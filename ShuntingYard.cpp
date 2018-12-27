
#include "ShuntingYard.h"
#include "MapHolder.h"


ShuntingYard::ShuntingYard() {
    initializeMap();
}

void ShuntingYard::initializeMap() {
    this->prcedence.insert(pair<char, int>('/', 2));
    this->prcedence.insert(pair<char, int>('*', 2));
    this->prcedence.insert(pair<char, int>('+', 1));
    this->prcedence.insert(pair<char, int>('-', 1));
    this->prcedence.insert(pair<char, int>(')', 0));
    this->prcedence.insert(pair<char, int>('(', 0));
}

int ShuntingYard::precedence(char operation) {
    if (this->prcedence.count(operation)) {
        return this->prcedence.at(operation);
    }
    throw "invalid operation!";
}

Expression *ShuntingYard::applyOp(Expression *val1, Expression *val2, char operation) {
    switch (operation) {
        case '*':
            return new Mul(val1, val2);
        case '/':
            return new Div(val1, val2);
        case '+':
            return new Plus(val1, val2);
        case '-':
            return new Minus(val1, val2);
    }
}

// Function that returns value of
// expression after evaluation.
Expression *ShuntingYard::createExpression(string tokens) {
    mutex mutex1;
    int i;
    enum LastPush {OP, VAL};
    LastPush lastPush;
    bool treatedMinus = false;
    // stack to store integer values.
    stack<Expression *> values;

    // stack to store operators.
    stack<char> ops;

    // replace possible vars of the expression-to-be
    MapHolder* mapHolder = MapHolder::getInstance();
    mutex1.lock();
    vector<string> vars = mapHolder->getVars();
    map<string, double> symbols = mapHolder->getSymbolTable();
    mutex1.unlock();
    double replaceValue;
    for (int i = 0; i < vars.size(); ++i) {
        size_t found = tokens.find(vars[i]);
        while (found != string::npos) {
            if (symbols.count(vars[i])) {
                replaceValue = symbols.at(vars[i]);
                string strRepVal = to_string(replaceValue);
                // Replace (vars[i].size) characters from "found-th" index with strRepVal
                tokens.replace(found, vars[i].length(), strRepVal);
            }
            //found += vars[i].length();
            found = tokens.find(vars[i]);
        }
    }


    for (i = 0; i < tokens.length(); i++) {

        // Current token is a whitespace,
        // skip it.
        if (tokens[i] == ' ')
            continue;

            // Current token is an opening
            // brace, push it to 'ops'
        else if (tokens[i] == '(') {
            ops.push(tokens[i]);
        }

            // Current token is a number, push
            // it to stack for numbers.
        else if (isdigit(tokens[i])) {
            double val = 0;
            // There may be more than one
            // digits in number.
            string tempNum;
            while (i < tokens.length() && (isdigit(tokens[i]) || tokens[i] == '.')) {
                tempNum += tokens[i];
                i++;
            }
            i--;
            val = stod(tempNum);
            Expression *num = new Num(val);
            values.push(num);
            lastPush = VAL;
        }

            // Closing brace encountered, solve
            // entire brace.
        else if (tokens[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                Expression *val2 = values.top();
                values.pop();

                Expression *val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
                treatedMinus = false;
            }

            // pop opening brace.
            ops.pop();
        }

            // Current token is an operator.
        else {
            char iToken = tokens[i];
            bool pushOp = true;
            if (tokens[i] == '+') {
               if ((ops.empty() && values.empty()) || lastPush == OP) {
                   pushOp = false;
               }
            } else if (tokens[i] == '-') {
                if ((ops.empty() && values.empty()) || lastPush == OP) {
                    if (!ops.empty() && ((ops.top() == '*') || (ops.top() == '/'))) {
                        Expression *num = new Num(-1);
                        values.push(num);
                        ops.push('*');
                        lastPush = OP;
                        pushOp = false;
                    } else if (!ops.empty() && (ops.top() == '+')) {
                        ops.pop();
                    }
                    else {
                        Expression *num = new Num(0);
                        values.push(num);
                        lastPush = VAL;
                    }
                    treatedMinus = true;
                }
            }
            // While top of 'ops' has same or greater
            // precedence to current token, which
            // is an operator. Apply operator on top
            // of 'ops' to top two elements in values stack.
//            else {
                while ((values.size() >= 2) && !ops.empty() && precedence(ops.top())
                                       >= precedence(tokens[i])) {
                    if (tokens[i] == '-' && treatedMinus) {
                        treatedMinus = false;
                        break;
                    }
                    Expression *val2 = values.top();
                    values.pop();

                    Expression *val1 = values.top();
                    values.pop();

                    char op = ops.top();
                    ops.pop();

                    values.push(applyOp(val1, val2, op));
                }
//            }

            // Push current token to 'ops'.
            if (pushOp) {
                ops.push(tokens[i]);
                lastPush = OP;
            }
        }
    }

    // Entire expression has been parsed at this
    // point, apply remaining ops to remaining
    // values.
    while (!ops.empty()) {
        Expression *val2 = values.top();
        values.pop();

        Expression *val1 = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(applyOp(val1, val2, op));
    }

    // Top of 'values' contains result, return it.
    return values.top();
}

bool ShuntingYard::isOperator(char token) {
    for (auto &item: operators) {
        if (token == item) {
            return true;
        }
    }
    return false;
}


///






