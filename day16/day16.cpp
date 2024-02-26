//
// Created by hkoertge on 26.02.2024.
//

#include "day16.h"
#include "../util.h"

using namespace std;

class Dance {
public:
    vector<char> programs;
    Dance() {
        for (char i = 'a'; i <= 'p'; i++) {
            programs.push_back(i);
        }
    }
    void spin(int x) {
        vector<char> newPrograms;
        for (int i = programs.size()-x; i < programs.size(); i++) {
            newPrograms.push_back(programs[i]);
        }
        for (int i = 0; i < programs.size()-x; i++) {
            newPrograms.push_back(programs[i]);
        }
        programs = newPrograms;
    }
    void exchange(int a, int b) {
        swap(programs[a], programs[b]);
    }
    void partner(char a, char b) {
        int indexA = -1;
        int indexB = -1;
        for (int i = 0; i < programs.size(); i++) {
            if (programs[i] == a) {
                indexA = i;
            }
            if (programs[i] == b) {
                indexB = i;
            }
        }
        swap(programs[indexA], programs[indexB]);
    }
};

Dance dance = Dance();

string Day16::part_1(string input) {
    input.pop_back(); // remove newline
    vector<string> moves = splitString(input, ",");
    for (const string& move: moves) {
        if (move[0] == 's') {
            dance.spin(stoi(move.substr(1)));
        } else if (move[0] == 'x') {
            vector<string> parts = splitString(move.substr(1), "/");
            dance.exchange(stoi(parts[0]), stoi(parts[1]));
        } else if (move[0] == 'p') {
            dance.partner(move[1], move[3]);
        }
    }
    return string(dance.programs.begin(), dance.programs.end());
}

string Day16::part_2(string input) {
    dance = Dance();
    string str;
    for (int i = 1000000000; i > 0; i--) {
        if (str == "abcdefghijklmnop") {
            int cl = 1000000000 - i;
            i %= cl;
        }
        str = part_1(input);
    }
    return str;
}