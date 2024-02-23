//
// Created by hkoertge on 23.02.2024.
//

#include "day12.h"
#include "../util.h"
#include <map>
#include <algorithm>

using namespace std;

string Day12::part_1(string input) {
    vector<string> lines = splitString(input, "\n");
    lines.pop_back();
    map<int, vector<int>> pipes;
    for (const string& line: lines) {
        vector<string> parts = splitString(line, " ");
        int pipe = stoi(parts[0]);
        vector<int> connections;
        for (int i = 2; i < parts.size(); i++) {
            connections.push_back(stoi(parts[i]));
        }
        pipes[pipe] = connections;
    }
    vector<int> group;
    vector<int> stack;
    group.push_back(0);
    stack.push_back(0);
    while (!stack.empty()) {
        int current = stack.back();
        stack.pop_back();
        for (int i: pipes[current]) {
            if (find(group.begin(), group.end(), i) == group.end()) {
                group.push_back(i);
                stack.push_back(i);
            }
        }
    }
    return to_string(group.size());
}

string Day12::part_2(string input) {
    vector<string> lines = splitString(input, "\n");
    lines.pop_back();
    map<int, vector<int>> pipes;
    for (const string& line: lines) {
        vector<string> parts = splitString(line, " ");
        int pipe = stoi(parts[0]);
        vector<int> connections;
        for (int i = 2; i < parts.size(); i++) {
            connections.push_back(stoi(parts[i]));
        }
        pipes[pipe] = connections;
    }
    vector<int> visited;
    int groups = 0;
    for (auto& i: pipes) {
        if (find(visited.begin(), visited.end(), i.first) == visited.end()) {
            groups++;
            visited.push_back(i.first);
            vector<int> group;
            vector<int> stack;
            group.push_back(i.first);
            stack.push_back(i.first);
            while (!stack.empty()) {
                int current = stack.back();
                stack.pop_back();
                for (int j: pipes[current]) {
                    if (find(group.begin(), group.end(), j) == group.end()) {
                        visited.push_back(j);
                        group.push_back(j);
                        stack.push_back(j);
                    }
                }
            }
        }
    }
    return to_string(groups);
}