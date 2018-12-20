//
// Created by noa on 12/17/18.
//



#include "Lexer.h"
#include <fstream>

vector<string> Lexer::lex(string name) {
    vector<string> lexi;
    string line;
    ifstream fileReader("a.txt");
    string delimiter = " ";
    string token;
    if (fileReader.is_open()) {
        while (fileReader.good()) {
            getline(fileReader, line);
            int pos = 0;
            while ((pos = line.find(delimiter)) != string::npos) {
                token = line.substr(0, pos);
                lexi.push_back(token);
                line.erase(0, pos + delimiter.length());
            }
        }
        fileReader.close();
    } else cout << "Unable to open file";

}



