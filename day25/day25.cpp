//
// Created by hkoertge on 11.03.2024.
//

#include "day25.h"
#include "../util.h"
#include <map>

using namespace std;

struct operation {
    bool write;
    int move;
    char next;
};
struct rule {
    operation zero;
    operation one;
};
map<char, rule> rules25;

map<long long, bool> tape;
long long cursor = 0;
char state;
int diagnosticChecksum;

void parseInput(string input) {
    vector<string> parts = splitString(input, "\n\n");
    vector<string> start = splitString(parts[0], "\n");
    start[0].pop_back();
    state = start[0].back();
    vector<string> words = splitString(start[1], " ");
    words.pop_back();
    diagnosticChecksum = stoi(words.back());
    parts.erase(parts.begin());
    for (string part: parts) {
        vector<string> lines = splitString(part, "\n");
        rule r = rule();
        r.zero.write = lines[2][22] == '1';
        r.one.write = lines[6][22] == '1';
        r.zero.move = splitString(lines[3], " ").back() == "right." ? 1 : -1;
        r.one.move = splitString(lines[7], " ").back() == "right." ? 1 : -1;
        r.zero.next = lines[4][26];
        r.one.next = lines[8][26];
        rules25[lines[0][9]] = r;
    }
}

string Day25::part_1(string input) {
    parseInput(input);
    for (int i = 0; i < diagnosticChecksum; i++) {
        operation o = tape[cursor] ? rules25[state].one : rules25[state].zero;
        tape[cursor] = o.write;
        cursor += o.move;
        state = o.next;
    }
    auto count = 0;
    for (const auto& t: tape) {
        if (t.second) {
            count++;
        }
    }
    return to_string(count);
}

string Day25::part_2(string input) {
    return "";
}
