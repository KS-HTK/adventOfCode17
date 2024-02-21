//
// Created by KS-HTK on 20.02.2024.
//

#include "Day.h"

string Day::get_input() {
    ifstream File(PATH);
    if (File.is_open()) {
        string input((istreambuf_iterator<char>(File)), (istreambuf_iterator<char>()));
        return input;
    }
    else {
        throw runtime_error(("File could not be opened! " + PATH));
    }
}

string Day::part_1(string input) {
    throw logic_error("Function not Implemented.");
}

string Day::part_2(string input) {
    throw logic_error("Function not Implemented.");
}

int Day::run_day() {
    string input;
    try {
        input = get_input();
    }
    catch (int err) {
        cout << err << endl;
        cout << PATH << endl;
        return -1;
    }
    cout << "Part 1: " << part_1(input) << endl;
    cout << "Part 2: " << part_2(input) << endl;
    return 0;
}