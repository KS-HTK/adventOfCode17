//
// Created by KS-HTK on 20.02.2024.
//

#include "..\Day.h"

#ifndef ADVENTOFCODE17_DAY02_H
#define ADVENTOFCODE17_DAY02_H

#endif //ADVENTOFCODE17_DAY02_H

#ifdef __cplusplus
extern "C" {
#endif

class Day02: public Day {
public:
    Day02(): Day(".\\day02\\input") { };
    string part_1(string) override;
    string part_2(string) override;
};

#ifdef __cplusplus
} // end extern "C"
#endif