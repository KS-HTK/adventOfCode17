//
// Created by KS-HTK on 20.02.2024.
//

#include "..\Day.h"

#ifndef ADVENTOFCODE17_DAY01_H
#define ADVENTOFCODE17_DAY01_H

#endif //ADVENTOFCODE17_DAY01_H

#ifdef __cplusplus
extern "C" {
#endif

class Day01: public Day {
public:
    Day01(): Day(".\\day01\\input") { };
    string part_1(string) override;
    string part_2(string) override;
};

#ifdef __cplusplus
} // end extern "C"
#endif