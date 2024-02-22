//
// Created by hkoertge on 22.02.2024.
//

#include "util.h"

vector<string> splitString(string str, const string& delimiter) {
    vector<string> tokens;
    size_t pos;
    while ((pos = str.find(delimiter)) != string::npos) {
        tokens.push_back(str.substr(0, pos));
        str.erase(0, pos + delimiter.length());
    }
    tokens.push_back(str);
    return tokens;
}