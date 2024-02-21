//
// Created by KS-HTK on 21.02.2024.
//

#include <algorithm>
#include <vector>
#include <sstream>
#include "day04.h"

string Day04::part_1(string input) {
    auto splitString = [](const string& str)-> vector<string> {
        vector<string> tokens;
        istringstream iss(str);
        string token;

        while (iss >> token) {
            tokens.push_back(token);
        }

        return tokens;
    };

    auto stringInVector = [](const vector<string>& v, const string& str) -> bool {
        return find(v.begin(), v.end(), str) != v.end();
    };

    int valid = 0;

    string delimiter = "\n";
    size_t pos = 0;
    while ((pos = input.find(delimiter)) != string::npos) {
        string st;
        st = input.substr(0, pos);

        vector<string> words = splitString(st);
        while (!words.empty()) {
            string word = words.back();
            words.pop_back();
            if (stringInVector(words, word)) break;
        }
        if (words.empty()) valid++;

        input.erase(0, pos + delimiter.length());
    }

    return to_string(valid);
}

string Day04::part_2(string input) {
    return to_string(-1);
}
