//
// Created by hkoertge on 22.02.2024.
//

#include "..\Day.h"
#include <vector>

#ifndef ADVENTOFCODE17_DAY07_H
#define ADVENTOFCODE17_DAY07_H

#endif //ADVENTOFCODE17_DAY07_H

#ifdef __cplusplus
extern "C" {
#endif

class Node {
public:
    string name;
    int weight;
    vector <string> c_list;
    vector<Node *> children;
    bool has_parents;
    Node() = default;
    Node(const string &name, int weight, vector <string> c_list);
    void setHasParent();
    string as_string();
    int getTotalWeight();
private:
    string name_list();

};

class Day07: public Day {
public:
    Day07(): Day(".\\day07\\input") { };
    string part_1(string) override;
    string part_2(string) override;
};

#ifdef __cplusplus
} // end extern "C"
#endif
