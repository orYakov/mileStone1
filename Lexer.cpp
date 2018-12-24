//
// Created by noa on 12/17/18.
//



#include "Lexer.h"
#include <fstream>

vector<string> Lexer::lex(string name) {
    vector<string> lexi;
    string line;
    ifstream fileReader(name);
    string delimiter = " ";
    string token;
    //fileReader.open(name);
    if (fileReader.is_open()) {
        while (fileReader.good()) {
            getline(fileReader, line);
            if (isWhiteSpace(line)) {
                continue;
            }
            line += " ";
            int quots;
            while ((quots = line.find("\"")) != string::npos) {
                line.erase(line.begin() + quots, line.begin() +(quots + 1));
            }
            int pos = 0;
            while ((pos = line.find(delimiter)) != string::npos) {
                token = line.substr(0, pos);
                lexi.push_back(token);
                line.erase(0, pos + delimiter.length());
            }
            contract(lexi);
            lexi.push_back("@"); // mark of end of line
        }
        fileReader.close();
    } else cout << "Unable to open file";
    return lexi;
}

void Lexer::contract(vector<string> &line) {
    string temp;
    for (int i = 0; i < line.size(); ++i) {
        if (isOperator(line[i]) && (i > 0)) {
            // Minus situation
            if (line[i] == "-") {
                if ((line[i -1] == "=") || (isOperator(line[i -1]))) {
                    temp = line[i] + line[i + 1];
                    line[i] = temp;
                    line.erase((line.begin() + i + 1));
                    continue;
                }
            }
            temp = line[i - 1] + line[i] + line[i + 1];
            line[i - 1] = temp;
            line.erase((line.begin() + i), (line.begin() + i + 1));
            --i;
        }
    }
}

bool Lexer::isOperator(string str) {
    return ((str == "+") || (str == "-") || (str == "*") || (str == "/"));
}

bool Lexer::isWhiteSpace(string str) {
    return ((str == "") || (str == " ") || (str == "\n") || (str == "\t") || (str == "\r"));
}




