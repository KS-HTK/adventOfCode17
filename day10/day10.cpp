//
// Created by hkoertge on 23.02.2024.
//

#include "day10.h"
#include "../util.h"
#include <algorithm>
#include <sstream>

using namespace std;

vector<int>& run_hash(vector<int>& list, vector<int>& lengths, int rounds) {
    int pos = 0;
    int skip = 0;
    while (rounds > 0) {
        for (int l: lengths) {
            vector<int> sublist;
            for (int i = 0; i < l; i++) {
                sublist.push_back(list[(pos + i) % list.size()]);
            }
            reverse(sublist.begin(), sublist.end());
            for (int i = 0; i < l; i++) {
                list[(pos + i) % list.size()] = sublist[i];
            }
            pos += l + skip;
            skip++;
        }
        rounds--;
    }
    return list;
}

string Day10::part_1(string input) {
    vector<string> lengthsStr = splitString(input, ",");
    vector<int> lengths;
    for_each(lengthsStr.begin(), lengthsStr.end(), [&lengths](const string& s) -> void {lengths.push_back(stoi(s));});
    vector<int> list(256);
    for (int i = 0; i < list.size(); i++) {
        list[i] = i;
    }
    run_hash(list, lengths, 1);
    return to_string(list[0] * list[1]);
}

string Day10::part_2(string input) {
    input.pop_back();
    vector<int> lengths;
    for_each(input.cbegin(), input.cend(), [&lengths](const char& c) -> void {lengths.push_back(c);});
    vector<int> suffix = {17, 31, 73, 47, 23};
    for_each(suffix.begin(), suffix.end(), [&lengths](const int& i) -> void {lengths.push_back(i);});
    vector<int> list(256);
    for (int i = 0; i < list.size(); i++) {
        list[i] = i;
    }
    run_hash(list, lengths, 64);
    // XOR the elements in groups of 16
    vector<int> dense_hash(16);
    while (!list.empty()) {
        int value = list[0];
        for (int i = 1; i < 16; i++) {
            value ^= list[i];
        }
        dense_hash.push_back(value);
        list.erase(list.begin(), list.begin() + 16);
    }
    stringstream res;
    for (int i: dense_hash) {
        res << hex << i;
    }
    size_t pos = res.str().find_first_not_of('0');
    return res.str().substr(pos);
}