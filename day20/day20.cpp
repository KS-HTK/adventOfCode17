//
// Created by hkoertge on 01.03.2024.
//

#include "day20.h"
#include "../util.h"
#include <algorithm>

using namespace std;

vector<vector<int>> parseParticles(const vector<string>& lines) {
    vector<vector<int>> particles;
    for (const string& line: lines) {
        vector<int> particle;
        for (const string& part: splitString(line, ", ")) {
            for (const string& num: splitString(part.substr(3, part.size()-1), ",")){
                particle.push_back(stoi(num));
            }
        }
        particles.push_back(particle);
    }
    return particles;
}

bool compare(const vector<int>& a, const vector<int>& b) {
    int aDist = 0;
    int bDist = 0;
    for (int i = 6; i < 9; i++) {
        aDist += abs(a[i]);
        bDist += abs(b[i]);
    }
    if (aDist == bDist) {
        aDist = 0;
        bDist = 0;
        for (int i = 3; i < 6; i++) {
            aDist += abs(a[i]);
            bDist += abs(b[i]);
        }
    }
    if (aDist == bDist) {
        aDist = 0;
        bDist = 0;
        for (int i = 0; i < 3; i++) {
            aDist += abs(a[i]);
            bDist += abs(b[i]);
        }
    }
    return aDist < bDist;
}

int findIndex(const std::vector<std::string>& lines, const std::string& substring) {
    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i].find(substring) == 0) {
            return i;
        }
    }
    return -1; // Not found
}

string Day20::part_1(string input) {
    vector<string> lines = splitString(input, "\n");
    lines.pop_back();
    vector<vector<int>> particles = parseParticles(lines);
    sort(particles.begin(), particles.end(), compare);
    string p = "p=<" + to_string(particles[0][0]) + "," + to_string(particles[0][1]) + "," + to_string(particles[0][2]) + ">";
    return to_string(findIndex(lines, p));
}

bool compare2(const vector<int>& a, const vector<int>& b) {
    return a[0] == b[0] && a[1] == b[1] && a[2] == b[2];
}

string Day20::part_2(string input) {
    vector<string> lines = splitString(input, "\n");
    lines.pop_back();
    vector<vector<int>> particles = parseParticles(lines);
    for (int i = 0; i < 40; i++) {
        vector<vector<int>> unique;
        for (int j = 0; j < particles.size(); j++) {
            bool duplicate = false;
            for (int k = 0; k < particles.size(); k++) {
                if (j == k) continue;
                duplicate |= compare2(particles[j], particles[k]);
                if (duplicate) break;
            }
            if (!duplicate) {
                unique.push_back(particles[j]);
            }
        }
        particles = unique;
        for (vector<int>& particle: particles) {
            for (int j = 0; j < 3; j++) {
                particle[j+3] += particle[j+6];
                particle[j] += particle[j+3];
            }
        }
    }
    return to_string(particles.size());
}