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

    if ((*check)[0].y != 0) {
        return false;
    }

    return true;
}

bool checkDone(int *seqPointer, Sequence *seq, int idx) {
    return seqPointer[idx] == (seq[idx].length - 1);
}

int calculateReward(int buffer, string input, string *solution, int width, int height, string *matrix, Sequence *seq, int seqAmount, int *seqPointer, Coordinate **coor) {
    *coor = new Coordinate[buffer];
    bool valid = turnCheck(buffer, input, coor);

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

            if (matrix[(*coor)[i].y * width + (*coor)[i].x] == seq[a].set[seqPointer[a]]) {
                seqPointer[a]++;
            }
            else {
                seqPointer[a] = 0;
            }

            if (checkDone(seqPointer, seq, a)) {
                result += seq[a].reward;
                seqPointer[a] = 0;
                cout << "sequence yg ngasih nilai tuh " << a << endl;
                cout << "current result " << result << endl;
                cout << "current sequence ";
                for (int i = 0; i < buffer; i++) {
                    cout << matrix[(*coor)[i].y * width + (*coor)[i].x] << " ";
                } 
                cout << endl << endl;
            }
        }
    }

    for (int i = 0; i < seqAmount; i++) {
        seqPointer[i] = 0;
    }
    *solution = input;
    return result;
}

// Function to generate all combinations of length n
void generateCombinations(const int width, const int height, const int n, vector<string>& combinations, string current, int x, int y) {
    if (n == 0) {
        combinations.push_back(current);
        return;
    }

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newX = x + i;
            int newY = y + j;

            if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                string newCoord = current + "(" + to_string(newX) + "," + to_string(newY) + ") ";
                generateCombinations(width, height, n - 1, combinations, newCoord, newX, newY);
            }
        }
    }
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

    vector<string> combinations;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            generateCombinations(width, height, buffer, combinations, "", i, j);
        }
    }
    
    // ngitung reward
    int max = 0, temp;
    Coordinate *coor, *resultCoor;
    for (const auto &combination : combinations) {
        temp = calculateReward(buffer, combination, &solutionTemp, width, height, matrix, seq, seqAmount, seqPointer, &coor);
        if (temp > max) {
            max = temp;
            solution = solutionTemp;
            resultCoor = coor;
        }
    }

    clock_t stop = clock();
    double timeTaken = (double)(stop - start) / CLOCKS_PER_SEC;
    cout << "Done!" << endl;
    cout << "Time taken: " << timeTaken << endl;
    cout << "Max value: " << max << endl;
    cout << "Buffer solution: ";
    for (int i = 0; i < buffer; i++) {
        cout << matrix[resultCoor[i].y * width + resultCoor[i].x] << " ";
    } 
    cout << endl;
    cout << "Buffer solution's coordinate: " << solution << endl;
}