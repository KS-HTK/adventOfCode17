//
// Created by hkoertge on 01.03.2024.
//

#include "day21.h"
#include "../util.h"
#include <map>
#include <algorithm>
#include <numeric>

using namespace std;

map<vector<vector<bool>>, vector<vector<bool>>> rules;

vector<vector<bool>> parsePattern(const string& pattern) {
    vector<vector<bool>> result;
    vector<string> lines = splitString(pattern, "/");
    for (const string& line: lines) {
        vector<bool> row;
        for (char c: line) {
            row.push_back(c == '#');
        }
        result.push_back(row);
    }
    return result;
}

void parseRules(const vector<string>& lines) {
    for (const string& line: lines) {
        vector<string> parts = splitString(line, " => ");
        vector<vector<bool>> input = parsePattern(parts[0]);
        vector<vector<bool>> output = parsePattern(parts[1]);
        rules[input] = output;
    }
}

vector<vector<bool>> rotate(const vector<vector<bool>>& pattern) {
    vector<vector<bool>> result;
    for (int i = 0; i < pattern.size(); i++) {
        vector<bool> row;
        for (int j = 0; j < pattern.size(); j++) {
            row.push_back(pattern[pattern.size()-j-1][i]);
        }
        result.push_back(row);
    }
    return result;
}

vector<vector<bool>> flip(const vector<vector<bool>>& pattern) {
    vector<vector<bool>> result;
    for (int i = 0; i < pattern.size(); i++) {
        vector<bool> row;
        for (int j = 0; j < pattern.size(); j++) {
            row.push_back(pattern[i][pattern.size()-j-1]);
        }
        result.push_back(row);
    }
    return result;
}

vector<vector<bool>> findRule(vector<vector<bool>> pattern) {
    for (int i = 0; i < 4; i++) {
        if (rules.find(pattern) != rules.end()) {
            return rules[pattern];
        }
        pattern = rotate(pattern);
    }
    pattern = flip(pattern);
    for (int i = 0; i < 4; i++) {
        if (rules.find(pattern) != rules.end()) {
            return rules[pattern];
        }
        pattern = rotate(pattern);
    }
    return pattern; // No rule found, should not happen
}

vector<vector<bool>> image = {
        {false, true, false},
        {false, false, true},
        {true, true, true}
};

void enhance() {
    vector<vector<bool>> newImage;
    int size = image.size();
    int subSize = size % 2 == 0 ? 2 : 3;
    for (int j = 0; j < size; j += subSize) {
        vector<vector<bool>> subImageRow;
        for (int l = 0; l <= subSize; l++) {
            vector<bool> row = {};
            subImageRow.push_back(row);
        }
        for (int k = 0; k < size; k += subSize) {
            vector<vector<bool>> subImage;
            for (int l = 0; l < subSize; l++) {
                vector<bool> row;
                for (int m = 0; m < subSize; m++) {
                    row.push_back(image[j+l][k+m]);
                }
                subImage.push_back(row);
            }
            vector<vector<bool>> newSubImage = findRule(subImage);
            for (int l = 0; l < newSubImage.size(); l++) {
                subImageRow[l].insert(subImageRow[l].end(), newSubImage[l].begin(), newSubImage[l].end());
            }
        }
        for (const auto & l : subImageRow) {
            newImage.push_back(l);
        }
    }
    image = newImage;
}

string Day21::part_1(string input) {
    vector<string> lines = splitString(input, "\n");
    lines.pop_back();
    parseRules(lines);
    for (int i = 0; i < 5; i++) {
        enhance();
    }
    vector<int> lengths;
    for_each(image.begin(), image.end(), [&lengths](vector<bool> a) {
        lengths.push_back(count(a.begin(), a.end(), true));
    });
    return to_string(reduce(lengths.begin(), lengths.end()));
}

string Day21::part_2(string input) {
    if (image.size() == 3) {
        part_1(input);
    }
    for (int i = 5; i < 18; i++) {
        enhance();
    }
    vector<int> lengths;
    for_each(image.begin(), image.end(), [&lengths](vector<bool> a) {
        lengths.push_back(count(a.begin(), a.end(), true));
    });
    return to_string(reduce(lengths.begin(), lengths.end()));
}