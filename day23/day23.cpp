//
// Created by hkoertge on 01.03.2024.
//

#include "day23.h"
#include "../util.h"
#include <map>
#include <queue>
#include <condition_variable>
#include <utility>

using namespace std;

map<string, int> cmdToNum23 = {
        {"set", 0},
        {"sub", 1},
        {"mul", 2},
        {"jnz", 3}
};

class Duet23 {
private:
    vector<string> instructions;
    map<char, long long> reg;
    bool pt2 = false;
    int mulCount = 0;
public:
    long long execute() {
        while (reg['.'] < instructions.size() && reg['.'] >= 0) {
            vector<string> parts = splitString(instructions[reg['.']], " ");
            int command = cmdToNum23[parts[0]];
            char X = parts[1][0];
            long long Y = 0;
            if (parts.size() > 2) {
                if (parts[2][0] >= 'a' && parts[2][0] <= 'z') {
                    Y = reg[parts[2][0]];
                } else {
                    Y = stoi(parts[2]);
                }
            }
            switch (command) {
                case 0: // set
                    reg[X] = Y;
                    break;
                case 1: // sub
                    reg[X] -= Y;
                    break;
                case 2: // mul
                    reg[X] *= Y;
                    mulCount++;
                    break;
                case 3: // jnz
                    if (((X >= 'a' && X <= 'z') ? reg[X] : X - '0') != 0) {
                        reg['.'] += Y;
                        reg['.']--;
                    }
                    break;
                default:
                    cout << "Unknown command: " << instructions[reg['.']] << endl;
                    return mulCount;
            }
            reg['.']++;
        }
        return pt2 ? reg['h'] : mulCount;
    }
    explicit Duet23(vector<string> instructions, long long a = 0) {
        this -> instructions = std::move(instructions);
        reg['a'] = a;
        if (a == 1) pt2 = true;
    }
};

string Day23::part_1(string input) {
    vector<string> lines = splitString(input, "\n");
    lines.pop_back();
    Duet23 duet = Duet23(lines);
    return to_string(duet.execute());
}

string Day23::part_2(string input) {
    // Manual implementation and optimization of instructions.
    int b, c, h = 0;

    b = 105700;
    c = b + 17000;
    while (true) {
        for (int d = 2; d < b; d++) {
            if (d * 2 <= b && b % d == 0) {
                h++;
                if (b == c) return to_string(h);
                break;
            }
        }
        b += 17;
    }
}