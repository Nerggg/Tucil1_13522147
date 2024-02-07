#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "io/io.h"
using namespace std;

bool checkDone(int *seqPointer, Sequence *seq, int idx);

bool isValid(int x, int y) {
    int width = 6, height = 6;
    return x >= 0 && x < width && y >= 0 && y < height;
}

void generateCombinationsUtil(int x, int y, int n, string path, vector<string> &combinations) {
    // Base case: If n is 0, add the path to combinations
    if (n == 0) {
        combinations.push_back(path);
        return;
    }

    // Traverse all 8 adjacent cells of matrix[x][y] and recur for each valid coordinate
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newX = x + i;
            int newY = y + j;

            // Proceed only if the coordinate is valid and not visited before
            if (isValid(newX, newY)) {
                // Recur for the next coordinate with reduced n
                generateCombinationsUtil(newX, newY, n - 1, path + "(" + to_string(newX) + "," + to_string(newY) + ") ", combinations);
            }
        }
    }
}

// Function to generate all combinations of length n
vector<string> generateCombinations(int n) {
    vector<string> combinations;
    int width = 6, height = 6;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            generateCombinationsUtil(i, j, n - 1, "(" + to_string(i) + "," + to_string(j) + ") ", combinations);
        }
    }
    return combinations;
}


int main() {
    int buffer, width, height, seqAmount;
    string *matrix;
    Sequence *seq;
    readinput(&buffer, &width, &height, &matrix, &seq, &seqAmount);

    // pointer untuk masing2 sequence
    int *seqPointer = new int[seqAmount];
    for (int i = 0; i < seqAmount; i++) {
        seqPointer[i] = 0;
    }

vector<string> combinations = generateCombinations(3);
    
    // Display the generated combinations
    cout << "Generated combinations:\n";
    for (const auto &combination : combinations) {
        cout << combination << endl;
    }

}

bool checkDone(int *seqPointer, Sequence *seq, int idx) {
    return seqPointer[idx] == (sizeof(seq[idx].set)/sizeof(string));
}