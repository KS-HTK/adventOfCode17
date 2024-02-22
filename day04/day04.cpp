//
// Created by KS-HTK on 21.02.2024.
//

#include <algorithm>
#include <vector>
#include "day04.h"
#include "../util.h"

bool stringInVector(const vector<string>& v, const string& str) {
    return any_of(v.begin(), v.end(), [&str](const string& word) {return str == word;});
}

string Day04::part_1(string input) {
    vector<string> lines = splitString(input, "\n");
    lines.pop_back(); // remove empty last line
    int valid = 0;
    for (const string& line: lines) {
        vector<string> words = splitString(line, " ");
        bool hasDupe = false;
        while (!words.empty()) {
            string word = words.back();
            words.pop_back();
            if (stringInVector(words, word)) {
                hasDupe = true;
                break;
            }
        }
        if (!hasDupe) valid++;
    }

    return to_string(valid);
}

bool areAnagrams(const string& word1, const string& word2) {
    if (word1.length() != word2.length()) return false;
    string sortedW1 = word1;
    string sortedW2 = word2;
    sort(sortedW1.begin(), sortedW1.end());
    sort(sortedW2.begin(), sortedW2.end());
    return sortedW1 == sortedW2;
}

bool anagramInVector(const vector<string>& v, const string& str) {
    return any_of(v.begin(), v.end(), [&str](const string& word) {return areAnagrams(word, str);});
}

string Day04::part_2(string input) {
    vector<string> lines = splitString(input, "\n");
    lines.pop_back(); // remove empty last line
    int valid = 0;
    for (const string& line: lines) {
        vector<string> words = splitString(line, " ");
        bool hasDupe = false;
        while (!words.empty()) {
            string word = words.back();
            words.pop_back();
            if (anagramInVector(words, word)) {
                hasDupe = true;
                break;
            }
        }
        if (!hasDupe) valid++;
    }

    return to_string(valid);
}
