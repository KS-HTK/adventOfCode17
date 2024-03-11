//
// Created by hkoertge on 01.03.2024.
//

#include "day24.h"
#include "../util.h"
#include <map>
#include <list>
#include <algorithm>

using namespace std;

struct Part {
    int p1;
    int p2;
};

map<int, Part> parts;
void parseString(string input) {
    vector<string> lines = splitString(input, "\n");
    lines.pop_back();
    for (int i = 0; i < lines.size(); i++) {
        vector<string> strings = splitString(lines[i], "/");
        Part p = Part();
        p.p1 = stoi(strings[0]);
        p.p2 = stoi(strings[1]);
        parts[i] = p;
    }
}

list<int> getPartsByPort(int port) {
    list<int> result;
    for (const auto& p: parts) {
        if (p.second.p1 == port || p.second.p2 == port) {
            result.push_back(p.first);
        }
    }
    return result;
}

list<list<int>> bridges;
void getBridges(int port, const list<int>& bridge) {
    list<int> usableParts = getPartsByPort(port);
    usableParts.remove_if([&bridge](int elem) {
        return find(bridge.begin(), bridge.end(), elem) != bridge.end();
    });
    if (usableParts.empty()) {
        bridges.push_back(bridge);
        return;
    }
    for (int id: usableParts) {
        list<int> tmp = bridge;
        tmp.push_back(id);
        Part nextPart = parts.find(id)->second;
        int nextPort = nextPart.p1 == port ? nextPart.p2 : nextPart.p1;
        getBridges(nextPort, tmp);
    }
}

int valueBridge(const list<int>& bridge) {
    int sum = 0;
    for (int id: bridge) {
        sum += parts[id].p1 + parts[id].p2;
    }
    return sum;
}

string Day24::part_1(string input) {
    parseString(input);
    getBridges(0, {});
    int max = INT_MIN;
    for (list<int> bridge: bridges) {
        int value = valueBridge(bridge);
        if (value > max) {
            max = value;
        }
    }
    return to_string(max);
}

void vst(const list<int>& bridge) {
    for (int id: bridge) {
        cout << parts[id].p1 << "/" << parts[id].p2 << " ";
    }
    cout << endl;
}

string Day24::part_2(string input) {
    if (bridges.empty()) {
        parseString(input);
        getBridges(0, {});
    }
    unsigned long long longest = 0;
    int max = INT_MIN;
    for (const list<int>& bridge: bridges) {
        if (bridge.size() > longest) {
            longest = bridge.size();
            max = INT_MIN;
        }
        if (bridge.size() == longest) {
            int value = valueBridge(bridge);
            if (value > max) {
                max = value;
            }
        }
    }
    return to_string(max);
}
