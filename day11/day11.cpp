//
// Created by hkoertge on 23.02.2024.
//

#include "day11.h"
#include "../util.h"

using namespace std;

/*HEX GRID Coordinate System
  \ n  /
nw +--+ ne
  /    \
-+      +-
  \    /
sw +--+ se
  / s  \
*/

int max_dist = INT_MIN;
string Day11::part_1(string input) {
    input.pop_back(); // remove newline
    vector<string> directions = splitString(input, ",");
    int q = 0, r = 0;
    for (const string& dir: directions) {
        if (dir == "n") {
            r--;
        } else if (dir == "s") {
            r++;
        } else if (dir == "ne") {
            q--;
        } else if (dir == "sw") {
            q++;
        } else if (dir == "se") {
            q--;
            r++;
        } else if (dir == "nw") {
            q++;
            r--;
        }
        if ((q < 0 and r < 0) or (q > 0 and r > 0)) {
            max_dist = max(max_dist, abs(q) + abs(r));
        } else {
            max_dist = max(max_dist, max(abs(q), abs(r)));
        }
    }
    if ((q < 0 and r < 0) or (q > 0 and r > 0)) {
        return to_string(abs(q) + abs(r));
    } else {
        return to_string(max(abs(q), abs(r)));
    }
}

string Day11::part_2(string input) {
    if (max_dist == INT_MIN) {
        part_1(input);
    }
    return to_string(max_dist);
}