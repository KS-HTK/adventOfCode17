//
// Created by hkoertge on 22.02.2024.
//

#include "day08.h"
#include "../util.h"
#include <map>
#include <utility>

using namespace std;

map<string, int> reg;

Instruction::Instruction(string name, int value, function<bool()> comp) {
        this->name = std::move(name);
        this->value = value;
        this->comp = std::move(comp);
}

vector<Instruction> instructionParser(const vector<string>& lines) {
    vector<Instruction> out;
    for (const string& line: lines) {
        vector<string> words = splitString(line, " ");
        string name = words[0];
        int value = stoi(words[2]);
        if (words[1] == "dec") {
            value *= -1;
        }
        string reg_name = words[4];
        int comp_value = stoi(words[6]);
        function<bool()> compare;
        if (words[5] == "=="){
            compare = [reg_name, comp_value]() -> bool {
                return reg[reg_name] == comp_value;
            };
        }
        else if (words[5] == "!=") {
            compare = [reg_name, comp_value]() -> bool {
                return reg[reg_name] != comp_value;
            };
        }
        else if (words[5] == ">") {
            compare = [reg_name, comp_value]() -> bool {
                return reg[reg_name] > comp_value;
            };
        }
        else if (words[5] == "<") {
            compare = [reg_name, comp_value]() -> bool {
                return reg[reg_name] < comp_value;
            };
        }
        else if (words[5] == ">=") {
            compare = [reg_name, comp_value]() -> bool {
                return reg[reg_name] >= comp_value;
            };
        }
        else if (words[5] == "<=") {
            compare = [reg_name, comp_value]() -> bool {
                return reg[reg_name] <= comp_value;
            };
        }
        else {
            cout << words[5] << endl;
            throw invalid_argument("Invalid comparison operator.");
        }
        out.emplace_back(name, value, compare);
        if (!reg.contains(name)) {
            reg[name] = 0;
        }
        if (!reg.contains(reg_name)) {
            reg[reg_name] = 0;
        }
    }
    return out;
}

int totalMax = INT_MIN;

string Day08::part_1(string input) {
    vector<string> lines = splitString(input, "\n");
    lines.pop_back();
    vector<Instruction> instructions = instructionParser(lines);
    for (const Instruction& instruction: instructions) {
        if (instruction.comp()) {
            reg[instruction.name] += instruction.value;
        }
        if (reg[instruction.name] > totalMax) {
            totalMax = reg[instruction.name];
        }
    }
    int max = INT_MIN;
    for (const auto& p: reg) {
        if (p.second > max) {
            max = p.second;
        }
    }

    return to_string(max);
}

string Day08::part_2(string input) {
    if (totalMax == INT_MIN) {
        part_1(input);
    }
    return to_string(totalMax);
}