
#include "utilities.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

void sort_by_magnitude(vector<double>& vec) {
    sort(vec.begin(), vec.end(), [](double a, double b) {
        return abs(a) < abs(b);
    });

}

TypedArray<TypedArray<double>> read_matrix_csv(const string path) {
    TypedArray<TypedArray<double>> matrix;
    std::ifstream file(path);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file: " + path);
    }
    string line;
    while (getline(file, line)) {
        istringstream stream(line);
        TypedArray<double> row;
        string value;
        while (std::getline(stream, value, ',')) {
            row.set(row.size(), stod(value));
        }
        matrix.set(matrix.size(), row);
    }
    return matrix;
}

void write_matrix_csv(const TypedArray<TypedArray<double>> &matrix, const string path) {
    ofstream file(path);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file for writing: " + path);
    }

    for (int i = 0; i < matrix.size(); i++) {
        const TypedArray<double>& row = matrix.safe_get(i);
        for (int j = 0; j < row.size(); j++) {
            file << row.safe_get(j);
            if (j < row.size() - 1) {
                file << ",";
            }
        }
        file << endl;
    }
}

// Reads a text file and returns a word occurrence map
map<string, int> occurrence_map(const string path) {
    map<string, int> word_count;
    ifstream file(path);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file: " + path);
    }

    string word;
    char c;
    bool in_quotes = false;

    while (file.get(c)) {
        c = tolower(c);  // Convert to lowercase immediately

        // Handle quotes to track if we're inside quoted text
        if (c == '"') {
            if (!word.empty()) {
                word_count[word]++;
                word.clear();
            }
            in_quotes = !in_quotes;
            continue;
        }

        // If character is alphanumeric or single quote, add to current word
        if (isalnum(c) || c == '\'') {
            word += c;
        }
        // If we encounter any other character and have a word stored
        else if (!word.empty()) {
            // Check if word only contains valid characters
            bool valid = true;
            for (char ch : word) {
                if (!isalnum(ch) && ch != '\'') {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                word_count[word]++;
            }
            word.clear();
        }
    }

    // Handle the last word
    if (!word.empty()) {
        bool valid = true;
        for (char ch : word) {
            if (!isalnum(ch) && ch != '\'') {
                valid = false;
                break;
            }
        }
        if (valid) {
            word_count[word]++;
        }
    }

    return word_count;
}


