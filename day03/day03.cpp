//
// Created by KS-HTK on 21.02.2024.
//

#include <vector>
#include <algorithm>
#include <cmath>
#include "day03.h"

string Day03::part_1(string input) {
    auto abs = [](int d) -> int {
        if (d < 0) return -d;
        return d;
    };

    auto next = [](int c, int n) -> int {
        int t = (n-1)*2+1;
        return c*n+t*t;
    };

    int num = stoi(input);
    int count = 0;
    while (num > next(8, count)) {
        count++;
    }
    int d = -1;
    if (num <= next(2, count)) d=1;
    else if (num <= next(4, count)) d=3;
    else if (num <= next(6, count)) d=5;
    else if (num <= next(8, count)) d=7;
    else cout << "did something wrong!" << endl;
    int steps = count + abs(next(d, count)-num);
    return to_string(steps);
}

string Day03::part_2(string input) {
    int num = stoi(input);

    // Helper function to calculate the ring number for the given ID
    auto ringNumber = [](int id) -> int {
        if (id == 1) return 0;
        int layer = ceil((sqrt(id - 1) - 1) / 2);
        return layer;
    };

    // Helper function to calculate the total cells up to the given ring
    auto cellsUpToRing = [](int ring) -> int {
        if (ring == 0) return 1;
        return (ring * 2 - 1) * (ring * 2 - 1);
    };

    // Function to find the coordinates (x, y) for the given cell ID
    auto idToCoordinates = [ringNumber, cellsUpToRing](int id) -> pair<int, int>{
        if (id == 1) return {0, 0};
        int ring = ringNumber(id);
        int sideLength = ring * 2;
        int maxIdInRing = cellsUpToRing(ring) + sideLength * 4;
        int offset = maxIdInRing - id;
        int side = offset / sideLength;
        int position = offset % sideLength;

        switch (side) {
            case 0: return {ring - position, -ring};
            case 1: return {-ring, -ring + position};
            case 2: return {-ring + position, ring};
            case 3: return {ring, ring - position};
            default: return {0, 0}; // This should never happen
        }
    };

    auto next = [](int c, int n) -> int {
        int t = (n-1)*2+1;
        return c*n+t*t;
    };

    // Function to find the cell ID for the given coordinates (x, y)
    auto coordinatesToId = [next](int x, int y) -> int {
        int ring;
        int dir;
        int offset;
        if (abs(x) > abs(y)) {
            ring = abs(x);
            if (x < 0) {
                dir = 5;
                offset = -y;
            }
            else {
                dir = 1;
                offset = y;
            }
        }
        else {
            ring = abs(y);
            if (y < 0) {
                dir = 7;
                offset = x;
            }
            else {
                dir = 3;
                offset = -x;
            }
        }
        return next(dir, ring)+offset;
    };

    // Main function to get all neighboring cell IDs
    auto getNeighbors = [idToCoordinates, coordinatesToId](int id) -> vector<int> {
        vector<int> neighbors;
        auto [x, y] = idToCoordinates(id);

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue; // Skip the cell itself
                neighbors.push_back(coordinatesToId(x + dx, y + dy));
            }
        }
        sort(neighbors.begin(), neighbors.end());
        return neighbors;
    };

    auto vstring = [](const vector<int>& ints) -> string {
        string s = "{";
        for (int i: ints) s += " " + to_string(i);
        return s+"}";
    };

    vector<int> ints;
    ints.push_back(1);
    ints.push_back(1);
    int id = 3;
    while (ints.back() < num) {
        int sum = 0;
        for (int i: getNeighbors(id)) {
            if (i > id) {
                break;
            }
            sum += ints[i-1];
        }
        ints.push_back(sum);
        id++;
    }
    return to_string(ints.back());
}
