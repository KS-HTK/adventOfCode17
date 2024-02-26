//
// Created by hkoertge on 26.02.2024.
//

#include "day17.h"
#include "../util.h"
#include <cassert>

using namespace std;

class Spinlock {
public:
    vector<int> buffer;
    int position;
    int stepSize;
    Spinlock() = default;
    Spinlock(int stepSize): stepSize(stepSize), buffer({0}), position(0) {}
    void insert() {
        position = (position + stepSize) % buffer.size() + 1;
        buffer.insert(buffer.begin() + position, buffer.size());
    }
    void insert2(int v) {
        position = ((position + stepSize) % v) + 1;
        if (position == 1) {
            buffer.insert(buffer.begin()+1, v);
        }
    }
    int getAfterLast() {
        assert (buffer[position] == 2017);
        return buffer[(position + 1) % buffer.size()];
    }
    int getAfterZero() {
        assert (buffer[0] == 0);
        return buffer[1];
    }
};

string Day17::part_1(string input) {
    input.pop_back(); // remove newline
    Spinlock sl = Spinlock(stoi(input));
    for (int i = 1; i <= 2017; i++) {
        sl.insert();
    }
    return to_string(sl.getAfterLast());
}

string Day17::part_2(string input) {
    input.pop_back(); // remove newline
    Spinlock sl = Spinlock(stoi(input));
    for (int i = 1; i <= 50000000; i++) {
        sl.insert2(i);
    }
    return to_string(sl.getAfterZero());
}