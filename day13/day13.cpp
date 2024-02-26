//
// Created by hkoertge on 23.02.2024.
//

#include "day13.h"
#include "../util.h"
#include <map>
#include <functional>

using namespace std;

pair<map<int, int>, int> parseInput(const string& input) {
    vector<string> lines = splitString(input, "\n");
    lines.pop_back(); // remove newline
    map<int, int> firewall;
    int max_depth = INT_MIN;
    for (const string& line: lines) {
        vector<string> parts = splitString(line, ": ");
        int depth = stoi(parts[0]);
        firewall[depth] = stoi(parts[1]);
        max_depth = max(max_depth, depth);
    }
    return make_pair(firewall, max_depth);
}

string Day13::part_1(string input) {
    map<int, int> firewall;
    int max_depth;
    tie(firewall, max_depth) = parseInput(input);

    int severity = 0;
    int depth = 0;
    while (depth <= max_depth) {
        if (firewall.find(depth) != firewall.end()) {
            int range = firewall[depth];
            if (depth % (2*(range-1)) == 0) {
                severity += depth * range;
            }
        }
        depth++;
    }
    return to_string(severity);
}

string Day13::part_2(string input) {
    //input = "0: 3\n1: 2\n4: 4\n6: 4\n";

    map<int, int> firewall;
    firewall = parseInput(input).first;
    vector<function<bool(int)>> scanners;
    for (auto& pair: firewall) {
        int depth = pair.first;
        int range = pair.second;
        int mr =  2*(range-1);
        scanners.emplace_back([mr, depth](int time) -> bool {
            return ((time % mr) + (depth % mr)) % mr == 0;
        });
    }

    int delay = 0;
    bool notFound = true;
    while (notFound) {
        for (auto& scan: scanners) {
            if (scan(delay)) {
                delay++;
                goto continue2;
            }
        }
        notFound = false;
        continue2:;
    }
    return to_string(delay);
}