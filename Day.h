//
// Created by KS-HTK on 20.02.2024.
//

#include <iostream>
#include <string>
#include <fstream>
#include <utility>
using namespace std;

#ifndef AOCCPP_DAY_H
#define AOCCPP_DAY_H

#ifdef __cplusplus
extern "C" {
#endif

class Day {
private:
    string PATH;
    string get_input();

protected:
    explicit Day(string path): PATH(std::move(path)) { }

public:
    virtual string part_1(string) = 0;
    virtual string part_2(string) = 0;
    int run_day();
};

#ifdef __cplusplus
}  // end extern "C"
#endif


#endif //AOCCPP_DAY_H
