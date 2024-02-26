//
// Created by hkoertge on 23.02.2024.
//

#include "day10.h"
#include "../util.h"
#include <algorithm>
#include <sstream>

using namespace std;

vector<int> reverse(const vector<int>& lengths, int rounds) {
    vector<int> list(256);
    for (int i = 0; i < list.size(); i++) {
        list[i] = i;
    }
    int pos = 0;
    int skip = 0;
    while (rounds > 0) {
        for (int l: lengths) {
            vector<int> sublist;
            for (int j = 0; j < l; j++) {
                sublist.push_back(list[(pos + j) % 256]);
            }
            for (int j = 0; j < l; j++) {
                list[(pos + l - 1 - j) % 256] = sublist[j];
            }
            pos += l + skip;
            skip++;
        }
        rounds--;
    }
    return list;
}

vector<int> dense(vector<int> list) {
    vector<int> dense_hash(16);
    for (int i = 0; i < 16; i++) {
        dense_hash[i] = list[i*16];
        for (int j = 1; j < 16; j++) {
            dense_hash[i] ^= list[i*16+j];
        }
    }
    return dense_hash;
}

string knot_hash(const vector<int>& list) {
    string knothash;
    for (int l: list) {
        stringstream ss;
        ss << hex << l;
        if (ss.str().size() == 1) {
            knothash += "0";
        }
        knothash += ss.str();
    }
    return knothash;
}

string Day10::part_1(string input) {
    vector<string> lengthsStr = splitString(input, ",");
    vector<int> lengths;
    for_each(lengthsStr.begin(), lengthsStr.end(), [&lengths](const string& s) -> void {lengths.push_back(stoi(s));});
    vector<int> list = reverse(lengths, 1);
    return to_string(list[0] * list[1]);
}

string Day10::part_2(string input) {
    input.pop_back();
    vector<int> lengths;
    for_each(input.cbegin(), input.cend(), [&lengths](const char& c) -> void {lengths.push_back(c);});
    vector<int> suffix = {17, 31, 73, 47, 23};
    for_each(suffix.begin(), suffix.end(), [&lengths](const int& i) -> void {lengths.push_back(i);});
    return knot_hash(dense(reverse(lengths, 64)));
}