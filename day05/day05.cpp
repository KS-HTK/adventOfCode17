//
// Created by KS-HTK on 21.02.2024.
//

#include <algorithm>
#include <vector>
#include "day05.h"
#include "../util.h"

string Day05::part_1(string input) {
    vector<string> lines = splitString(input, "\n");
    lines.pop_back(); // remove empty last line
    vector<int> inst;
    for (const string& line: lines) {
        inst.push_back(stoi(line));
    }
    int steps = 0;
    int ind = 0;
    while (ind >= 0 && ind < inst.size()) {
        int next = ind + inst[ind];
        inst[ind]++;
        ind = next;
        steps++;
    }
    return to_string(steps);
}

string Day05::part_2(string input) {
    vector<string> lines = splitString(input, "\n");
    lines.pop_back(); // remove empty last line
    vector<int> inst;
    for (const string& line: lines) {
        inst.push_back(stoi(line));
    }
    int steps = 0;
    int ind = 0;
    while (ind >= 0 && ind < inst.size()) {
        int next = ind + inst[ind];
        if (inst[ind] >= 3) inst[ind]--;
        else inst[ind]++;
        ind = next;
        steps++;
    }
    return to_string(steps);
}
