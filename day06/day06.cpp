//
// Created by KS-HTK on 21.02.2024.
//

#include <algorithm>
#include <vector>
#include "day06.h"
#include "../util.h"

vector<vector<int>> seen;

bool vInV(const vector<int>& v, const vector<vector<int>>& vv) {
    return any_of(vv.begin(), vv.end(), [v](const vector<int>& v2) -> bool { return v == v2; });
}

string Day06::part_1(string input) {
    vector<string> lines = splitString(input, "\n");
    string line = lines.front();
    vector<int> blocks;
    for (string& l: splitString(line, "\t")) {
        blocks.push_back(stoi(l));
    }
    while (!vInV(blocks, seen)) {
        seen.push_back(blocks);
        int max = *max_element(blocks.begin(), blocks.end());
        int maxIndex = distance(blocks.begin(), max_element(blocks.begin(), blocks.end()));
        blocks[maxIndex] = 0;
        for (int i = 0; i < max; i++) {
            blocks[(maxIndex + i + 1) % blocks.size()]++;
        }
    }
    seen.push_back(blocks);
    return to_string(seen.size() - 1);
}

string Day06::part_2(string input) {
    vector<int> blocks = seen.back();
    seen.pop_back();
    int cycles = seen.size();
    int firstOccurrence = distance(seen.begin(), find(seen.begin(), seen.end(), blocks));
    cycles -= firstOccurrence;
    return to_string(cycles);
}
