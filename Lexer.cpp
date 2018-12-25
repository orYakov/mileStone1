//
// Created by noa on 12/17/18.
//


#define LINE_SEPARATOR "@"
#include "Lexer.h"
#include <fstream>

vector<string> Lexer::lex(string name) {
    vector<string> lexi;
    string line;
    ifstream fileReader(name);
    string delimiter = " ";
    string token;
    vector<string> toContract;
    //fileReader.open(name);
    if (fileReader.is_open()) {
        while (fileReader.good()) {
            getline(fileReader, line);
            if (isWhiteSpace(line)) {
                continue;
            }
            line += " ";
            // remove quots of path
            int quots;
            while ((quots = line.find("\"")) != string::npos) {
                if (line.find("bind") == string::npos) { // if "bind" is not found, don't remove quots
                    break;
                }
                line.erase(line.begin() + quots, line.begin() +(quots + 1));
            }
            int pos = 0;
            while ((pos = line.find(delimiter)) != string::npos) {
                token = line.substr(0, pos);
                //lexi.push_back(token);
                line.erase(0, pos + delimiter.length());
                toContract.push_back(token);
            }
            contract(toContract);
            toContract.push_back(LINE_SEPARATOR);
            lexi.insert(lexi.end(), toContract.begin(), toContract.end());
            toContract.clear();
            //lexi.push_back("@"); // mark of end of line
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
            line.erase((line.begin() + i), (line.begin() + i + 2));
            i --;
        }
    }
}

bool Lexer::isOperator(string str) {
    return ((str == "+") || (str == "-") || (str == "*") || (str == "/"));
}

bool Lexer::isWhiteSpace(string str) {
    return ((str == "") || (str == " ") || (str == "\n") || (str == "\t") || (str == "\r"));
}
///



