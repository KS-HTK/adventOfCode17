//
// Created by KS-HTK on 21.02.2024.
//

#include "..\Day.h"

#ifndef AOCCPP_DAY01_H
#define AOCCPP_DAY01_H

#endif //AOCCPP_DAY01_H

#ifdef __cplusplus
extern "C" {
#endif

class Day05: public Day {
public:
    Day05(): Day(".\\day05\\input") { };
    string part_1(string) override;
    string part_2(string) override;
};

#ifdef __cplusplus
} // end extern "C"
#endif