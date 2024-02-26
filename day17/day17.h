//
// Created by hkoertge on 26.02.2024.
//

#include "..\Day.h"

#ifndef ADVENTOFCODE17_DAY17_H
#define ADVENTOFCODE17_DAY17_H

#endif //ADVENTOFCODE17_DAY17_H

#ifdef __cplusplus
extern "C" {
#endif

class Day17: public Day {
public:
    Day17(): Day(".\\day17\\input") { };
    string part_1(string) override;
    string part_2(string) override;
};

#ifdef __cplusplus
} // end extern "C"
#endif
