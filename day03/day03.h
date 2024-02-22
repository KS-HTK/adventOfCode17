//
// Created by KS-HTK on 21.02.2024.
//

#include "..\Day.h"

#ifndef ADVENTOFCODE17_DAY03_H
#define ADVENTOFCODE17_DAY03_H

#endif //ADVENTOFCODE17_DAY03_H

#ifdef __cplusplus
extern "C" {
#endif

class Day03: public Day {
public:
    Day03(): Day(".\\day03\\input") { };
    string part_1(string) override;
    string part_2(string) override;
};

#ifdef __cplusplus
} // end extern "C"
#endif