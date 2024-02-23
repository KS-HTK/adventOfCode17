//
// Created by hkoertge on 23.02.2024.
//

#include "day09.h"
#include "../util.h"

int pt2_score = 0;
string Day09::part_1(string input) {
    int sum = 0;
    vector<int> stack;
    int score = 1;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == '{') {
            stack.push_back(score);
            score++;
        } else if (input[i] == '}') {
            score--;
            sum += stack.back();
            stack.pop_back();
        } else if (input[i] == '<') {
            i++;
            while (input[i] != '>') {
                if (input[i] == '!') {
                    pt2_score--;
                    i++;
                }
                pt2_score++;
                i++;
            }
        }
    }
    return to_string(sum);
}

string Day09::part_2(string input) {
    if (pt2_score == 0) {
        part_1(input);
    }
    return to_string(pt2_score);
}