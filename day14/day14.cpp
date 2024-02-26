//
// Created by hkoertge on 26.02.2024.
//

#include "day14.h"
#include "../day10/day10.h"
#include "../util.h"
#include <vector>
#include <string>

using namespace std;

Day10 day10;

int countSetBits(char hexDigit) {
    int count = 0;
    int decimalValue;
    if (hexDigit >= '0' && hexDigit <= '9') {
        decimalValue = hexDigit - '0';
    } else if (hexDigit >= 'A' && hexDigit <= 'F') {
        decimalValue = hexDigit - 'A' + 10;
    } else if (hexDigit >= 'a' && hexDigit <= 'f') {
        decimalValue = hexDigit - 'a' + 10;
    } else {
        return -1; // Invalid hex digit
    }
    while (decimalValue != 0) {
        if (decimalValue % 2 == 1) {
            count++;
        }
        decimalValue /= 2;
    }
    return count;
}

string Day14::part_1(string input) {
    input.pop_back(); // remove newline
    int sum = 0;
    for (int i = 0; i < 128; i++) {
        string hash = day10.part_2(input+"-"+to_string(i)+"\n");
        for (char hexDigit : hash) {
            int setBits = countSetBits(hexDigit);
            sum += setBits;
        }
    }
    return to_string(sum);
}

int getBit(const string& hexString, int bitIndex) {
    int digitIndex = bitIndex / 4;
    int hexDigit = hexString[digitIndex];

    if (hexDigit >= '0' && hexDigit <= '9') {
        hexDigit -= '0';
    } else if (hexDigit >= 'A' && hexDigit <= 'F') {
        hexDigit = hexDigit - 'A' + 10;
    } else if (hexDigit >= 'a' && hexDigit <= 'f') {
        hexDigit = hexDigit - 'a' + 10;
    } else {
        return -1; // Invalid hex digit
    }
    int bitOffset = bitIndex % 4;
    return (hexDigit >> (3 - bitOffset)) & 1;
}

bool markRegion(const vector<string>& matrix, vector<vector<bool>>& visited, int row, int col) {
    int numRows = matrix.size();
    int numCols = matrix[0].size() * 4;
    if (row < 0 || row >= numRows || col < 0 || col >= numCols || getBit(matrix[row], col) != 1 || visited[row][col]) {
        return false;
    }
    visited[row][col] = true;
    markRegion(matrix, visited, row + 1, col);
    markRegion(matrix, visited, row - 1, col);
    markRegion(matrix, visited, row, col + 1);
    markRegion(matrix, visited, row, col - 1);
    return true;
}

int countRegions(const vector<string>& matrix) {
    int count = 0;
    int numRows = matrix.size();
    int numCols = matrix[0].size() * 4;
    vector<vector<bool>> visited(numRows, vector<bool>(numCols, false));
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (markRegion(matrix, visited, i, j)) count++;
        }
    }
    return count;
}

string Day14::part_2(string input) {
    input.pop_back(); // remove newline
    vector<string> matrix;
    for (int i = 0; i < 128; i++) {
        matrix.push_back(day10.part_2(input + "-" + to_string(i) + "\n"));
    }
    int regionCount = countRegions(matrix);
    return to_string(regionCount);
}