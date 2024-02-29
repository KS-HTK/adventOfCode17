//
// Created by hkoertge on 29.02.2024.
//

#include "day19.h"
#include "../util.h"
#include <map>

using namespace std;

pair<int, int> current, previous;

map<pair<int, int>, char> grid;
string pt1;
int pt2 = 0;

pair<int, int> getNext() {
    int dx = current.first - previous.first;
    int dy = current.second - previous.second;
    if (dx != 0 && grid[current] != '+') {
        pair<int, int> next = {current.first + dx, current.second};
        if (grid.find(next) != grid.end()) {
            return next;
        }
    }
    if (dy != 0 && grid[current] != '+') {
        pair<int, int> next = {current.first, current.second + dy};
        if (grid.find(next) != grid.end()) {
            return next;
        }
    }

    vector<pair<int, int>> neighbors = {{current.first+1, current.second},
                                        {current.first-1, current.second},
                                        {current.first, current.second+1},
                                        {current.first, current.second-1}};
    for (pair<int, int> p: neighbors) {
        if (grid.find(p) != grid.end()) {
            if (p != previous) {
                return p;
            }
        }
    }
    return {-1, -1};
}

void go() {
    pair<int, int> next = getNext();
    while (next != pair(-1, -1)) {
        previous = current;
        current = next;
        next = getNext();
        if (grid[current] >= 'A' && grid[current] <= 'Z') {
            pt1 += grid[current];
        }
        pt2++;
    }
}

string Day19::part_1(string input) {
    vector<string> lines = splitString(input, "\n");
    lines.pop_back();
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            char c = lines[i][j];
            if (c != ' ' && c != '\n') {
                grid[{i, j}] = c;
                if (i == 0) {
                    previous = {-2, j};
                    current = {-1, j};
                }
            }
        }
    }
    go();
    return pt1;
}

string Day19::part_2(string input) {
    if (pt2 == 0) {
        part_1(input);
    }
    return to_string(pt2);
}