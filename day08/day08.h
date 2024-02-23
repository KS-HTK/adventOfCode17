//
// Created by hkoertge on 22.02.2024.
//

#include "..\Day.h"
#include <vector>
#include <functional>

#ifndef ADVENTOFCODE17_DAY08_H
#define ADVENTOFCODE17_DAY08_H

#endif //ADVENTOFCODE17_DAY08_H

#ifdef __cplusplus
extern "C" {
#endif

using namespace std;

class Instruction {
public:
    string name;
    int value{};
    function<bool()> comp;
    Instruction() = default;
    Instruction(string name, int value, function<bool()> comp);
};

class Day08: public Day {
public:
    Day08(): Day(".\\day08\\input") { };
    string part_1(string) override;
    string part_2(string) override;
};

#ifdef __cplusplus
} // end extern "C"
#endif
