#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include "io/io.h"
using namespace std;

typedef struct {
    int x;
    int y;
} Coordinate;

bool turnCheck(int buffer, string input, Coordinate **check) {
    int pointer = 0;
    int xSize, ySize, xTemp, yTemp;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == '(') {
            xSize = 0;
        }
        else {
            xSize++;
        }

        if (input[i] == ',') {
            xTemp = stoi(input.substr(i-xSize+1, xSize-1));
            ySize = 0;
        }

        else {
            ySize++;
        }

        if (input[i] == ')') {
            yTemp = stoi(input.substr(i-ySize+1, ySize-1));
        }

        if (input[i] == ' ') {
            (*check)[pointer] = {xTemp, yTemp};
            pointer++;
        }
    }

    for (int i = 1; i < buffer; i++) {
        if (i % 2 != 0) {
            if ((*check)[i].x != (*check)[i-1].x || (*check)[i].y == (*check)[i-1].y) {
                return false;
            }
        }
        else if (i % 2 == 0) {
            if ((*check)[i].y != (*check)[i-1].y || (*check)[i].x == (*check)[i-1].x) {
                return false;
            }
        }
    }

    return true;
}

bool checkDone(int *seqPointer, Sequence *seq, int idx) {
    return seqPointer[idx] == (seq[idx].length - 1);
}

bool isValid(int x, int y, int width, int height) {
    return x >= 0 && x < width && y >= 0 && y < height;
}

int calculateReward(int buffer, string input, string *solution, int width, int height, string *matrix, Sequence *seq, int seqAmount, int *seqPointer) {
    Coordinate *coor = new Coordinate[buffer];
    bool valid = turnCheck(buffer, input, &coor);

    if (!valid) {
        return 0;
    }

    int result = 0;
    // cout << "input nya " << input << endl;
    for (int i = 0; i < buffer; i++) {
        // cout << "i nya " << i << endl;
        for (int a = 0; a < seqAmount; a++) {            
            // cout << "counter seqAmount nya " << a << endl;
            // cout << "pointernya ada di " << seqPointer[a] << endl;
            // cout << "sedangkan seq nya " << seq[a].set[seqPointer[a]] << endl;
            // cout << "nilai x dari coor nya " << coor[i].x << endl;
            // cout << "nilai y dari coor nya " << coor[i].y << endl;
            // cout << "sedangkan nilai matriks nya " << matrix[coor[i].y * width + coor[i].x] << endl;
            // cout << endl;

            if (matrix[coor[i].y * width + coor[i].x] == seq[a].set[seqPointer[a]]) {
                seqPointer[a]++;
            }
            else {
                seqPointer[a] = 0;
            }

            if (checkDone(seqPointer, seq, a)) {
                result += seq[a].reward;
                seqPointer[a] = 0;
                // cout << "sequence yg ngasih nilai tuh " << a << endl;
                // cout << "current result " << result << endl;
            }
        }
    }
    if (result == 50) {
        // cout << "pas 50, inputnya adalah " << input << endl;
    }
    *solution = input;
    return result;
}

void generateCombinationsUtil(int width, int height, int x, int y, int n, string path, vector<string> &combinations) {
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
            if (isValid(newX, newY, width, height)) {
                generateCombinationsUtil(width, height, newX, newY, n - 1, path + "(" + to_string(newX) + "," + to_string(newY) + ") ", combinations);                
            }
        }
    }
}

// Function to generate all combinations of length n
vector<string> generateCombinations(int n, int width, int height) {
    vector<string> combinations;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            generateCombinationsUtil(width, height, i, j, n - 1, "(" + to_string(i) + "," + to_string(j) + ") ", combinations);
        }
    }
    return combinations;
}


int main() {
    int buffer, width, height, seqAmount;
    string *matrix, solutionTemp, solution;
    Sequence *seq;
    readinput(&buffer, &width, &height, &matrix, &seq, &seqAmount);

    // pointer untuk masing2 sequence
    int *seqPointer = new int[seqAmount];
    for (int i = 0; i < seqAmount; i++) {
        seqPointer[i] = 0;
    }
 
    // begin main algorithm
    clock_t start = clock();
    vector<string> combinations = generateCombinations(buffer, width, height); 
    
    // Display the generated combinations
    int max = 0, temp;
    for (const auto &combination : combinations) {
        temp = calculateReward(buffer, combination, &solutionTemp, width, height, matrix, seq, seqAmount, seqPointer);
        if (temp > max) {
            max = temp;
            solution = solutionTemp;
        }
    }
    
    clock_t stop = clock();
    double timeTaken = (double)(stop - start) / CLOCKS_PER_SEC;
    cout << "Done!" << endl;
    cout << "Time taken: " << timeTaken << endl;
    cout << "Max value: " << max << endl;
    cout << "Buffer solution: " << solution << endl;
}