//
// Created by KS-HTK on 20.02.2024.
//

#include "day02.h"
#include <sstream>
#include <vector>

string Day02::part_1(string input) {
    string delimiter = "\n";
    int sum = 0;
    size_t pos = 0;
    while ((pos = input.find(delimiter)) != string::npos) {
        stringstream st;
        st << input.substr(0, pos);
        string temp;
        int found;
        int min = INT_MAX, max = INT_MIN;
        while (!st.eof()) {
            st >> temp;
            if (stringstream(temp) >> found) {
                if (found < min) min = found;
                if (found > max) max = found;
            }
            temp = "";
        }
        sum += max - min;
        input.erase(0, pos + delimiter.length());
    }

    return to_string(sum);
}

string Day02::part_2(string input) {
    string delimiter = "\n";
    int sum = 0;
    size_t pos = 0;
    while ((pos = input.find(delimiter)) != string::npos) {
        stringstream st;
        st << input.substr(0, pos);
        string temp;
        vector<int> ints;
        int found;
        while (!st.eof()) {  // find all ints in input line and store them in vector
            st >> temp;
            if (stringstream(temp) >> found) {
                ints.push_back(found);
            }
            temp = "";
        }
        while (!ints.empty()) {
            int first = ints.back();
            ints.pop_back();
            for(const int second : ints) {
                if (first > second and first % second == 0) {
                    sum += first/second;
                    break;
                }
                else if (second % first == 0) {
                    sum += second/first;
                    break;
                }
            }
        }
        input.erase(0, pos + delimiter.length());
    }
    return to_string(sum);
}
