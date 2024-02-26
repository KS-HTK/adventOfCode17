//
// Created by hkoertge on 26.02.2024.
//

#include "day15.h"
#include "../day10/day10.h"
#include "../util.h"
#include <vector>
#include <string>
#include <limits>

using namespace std;

class Generator {
    long factor;
    long divisor;
    long long value;
    int mod;
public:
    Generator() = default;
    Generator(long factor, long divisor, long value, int pt2mod): factor(factor), divisor(divisor), value(value), mod(pt2mod) {}
    long next() {
        value = value*factor % divisor;
        return value;
    }
    long next2() {
        value = value*factor % divisor;
        if (value % mod == 0) {
            return value;
        }
        return next2();
    }
};
long factorA = 16807;
long factorB = 48271;
long divisor = 2147483647;

bool judge(long a, long b) {
    const int mask = 0xFFFF; // Mask to extract lowest 16 bits
    return (a&mask) == (b&mask);
}

string Day15::part_1(string input) {
    vector<string> lines = splitString(input, "\n");
    lines.pop_back();
    int a = stoi(splitString(lines[0], " ")[4]);
    int b = stoi(splitString(lines[1], " ")[4]);
    Generator genA(factorA, divisor, a, 4);
    Generator genB(factorB, divisor, b, 8);
    int count = 0;
    for (int i = 0; i < 40000000; i++) {
        count += judge(genA.next(), genB.next());
    }
    return to_string(count);
}

string Day15::part_2(string input) {
    vector<string> lines = splitString(input, "\n");
    lines.pop_back();
    int a = stoi(splitString(lines[0], " ")[4]);
    int b = stoi(splitString(lines[1], " ")[4]);
    Generator genA(factorA, divisor, a, 4);
    Generator genB(factorB, divisor, b, 8);
    int count = 0;
    for (int i = 0; i < 5000000; i++) {
        count += judge(genA.next2(), genB.next2());
    }
    return to_string(count);
}