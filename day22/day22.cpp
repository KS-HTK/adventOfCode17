//
// Created by hkoertge on 01.03.2024.
//

#include "day22.h"
#include "../util.h"
#include <map>

using namespace std;

int x_pos;
int y_pos;
int dx;
int dy;

map<int, map<int, int>> infected;
// 0 = clean, 1 = weakened, 2 = infected, 3 = flagged
int infections;

void turnRight() {
    int temp = dx;
    dx = dy;
    dy = -temp;
}

void turnLeft() {
    int temp = dx;
    dx = -dy;
    dy = temp;
}

void burst(bool part2) {
    switch (infected[x_pos][y_pos]) {
        case 0:
            turnLeft();
            break;
        case 1:
            break;
        case 2:
            turnRight();
            break;
        case 3:
            dx = -dx;
            dy = -dy;
            break;
    }
    if (part2) {
        infected[x_pos][y_pos] = (infected[x_pos][y_pos] + 1) % 4;
        if (infected[x_pos][y_pos] == 2) infections++;
    } else {
        infected[x_pos][y_pos] = (infected[x_pos][y_pos] + 2) % 4;
        if (infected[x_pos][y_pos] == 2) infections++;
    }
    x_pos += dx;
    y_pos += dy;
}

string Day22::part_1(string input) {
    vector<string> lines = splitString(input, "\n");
    lines.pop_back();
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            infected[i][j] = (lines[i][j] == '#') ? 2 : 0;
        }
    }
    x_pos = lines.size() / 2;
    y_pos = lines[0].size() / 2;
    dx = -1;
    dy = 0;
    for (int i = 0; i < 10000; i++) {
        burst(false);
    }
    return to_string(infections);
}

string Day22::part_2(string input) {
    infections = 0;
    infected.clear();
    vector<string> lines = splitString(input, "\n");
    lines.pop_back();
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            infected[i][j] = (lines[i][j] == '#') ? 2 : 0;
        }
    }
    x_pos = lines.size() / 2;
    y_pos = lines[0].size() / 2;
    dx = -1;
    dy = 0;
    for (int i = 0; i < 10000000; i++) {
        burst(true);
    }
    return to_string(infections);
}