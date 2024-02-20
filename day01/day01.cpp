//
// Created by KS-HTK on 20.02.2024.
//

#include "day01.h"

string Day01::part_1(string input) {
    int il = input.length();
    input += input[0];
    int sum = 0;
    for (int i = 1; i <= il; i++) {
        if (input[i-1] == input[i]) {
            sum = sum + (input[i] - '0');
        }
    }
    return to_string(sum);
}

string Day01::part_2(string input) {
    int il = input.length();
    input += input;
    int sum = 0;
    for (int i = 0; i < il; i++) {
        int i2 = i+il/2;
        if (input[i] == input[i2]) {
            sum += (input[i] - '0');
        }
    }
    return to_string(sum);
}
