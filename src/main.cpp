#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <memory>
#include "io/io.h"
using namespace std;

typedef struct {
    int x;
    int y;
} Coordinate;

bool turnCheck(int buffer, string input, unique_ptr<Coordinate[]>& check) {
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
            check[pointer] = {xTemp, yTemp};
            pointer++;
        }
    }

    for (int i = 1; i < buffer; i++) {
        if (i % 2 != 0) {
            if (check[i].x != check[i-1].x || check[i].y == check[i-1].y) {
                return false;
            }
        }
        else if (i % 2 == 0) {
            if (check[i].y != check[i-1].y || check[i].x == check[i-1].x) {
                return false;
            }
        }
    }

    if (check[0].y != 0) {
        return false;
    }

    return true;
}

bool checkDone(int *seqPointer, Sequence *seq, int idx) {
    return seqPointer[idx] == (seq[idx].length);
}

int calculateReward(int buffer, string input, string *solution, int width, int height, string *matrix, Sequence *seq, int seqAmount, int *seqPointer, unique_ptr<Coordinate[]>& coor) {
    coor = make_unique<Coordinate[]>(buffer);
    bool valid = turnCheck(buffer, input, coor);

    if (!valid) {
        return 0;
    }

    int result = 0;
    for (int i = 0; i < buffer; i++) {
        for (int a = 0; a < seqAmount; a++) {            
            if (matrix[coor[i].y * width + coor[i].x] == seq[a].set[seqPointer[a]]) {
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
                    cout << matrix[coor[i].y * width + coor[i].x] << " ";
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
void generateCombinations(int width, int height, vector<pair<int, int>>& current, int n, vector<string>& combinations, int startX = 0, int startY = 0) {
    if (n == 0) {
        // Base case: if n is 0, concatenate the current combination into a string
        string combinationStr;
        for (auto& coord : current) {
            combinationStr += "(" + to_string(coord.first) + "," + to_string(coord.second) + ") ";
        }
        combinations.push_back(combinationStr);
        return;
    }

    // Recursive case: generate all possible combinations for the next coordinate
    for (int x = startX; x < width; ++x) {
        for (int y = startY; y < height; ++y) {
            current.push_back({x, y});
            generateCombinations(width, height, current, n - 1, combinations, x, y + 1);
            current.pop_back();
        }
        startY = 0; // Reset startY for new rows
    }
}

int main() {
    int buffer, width, height, seqAmount;
    string *matrix, solutionTemp, solution;
    Sequence *seq;
    readinput(&buffer, &width, &height, &matrix, &seq, &seqAmount);

    unique_ptr<int[]> seqPointer(new int[seqAmount]);
    for (int i = 0; i < seqAmount; i++) {
        seqPointer[i] = 0;
    }
 
    clock_t start = clock();

    vector<string> combinations;

    vector<pair<int, int>> current;
    // Ensuring the y axis of the first coordinate is always 0
    for (int x = 0; x < width; ++x) {
        current.push_back({x, 0});
        generateCombinations(width, height, current, buffer - 1, combinations);
        current.pop_back();
    }
    
    int max = 0, temp;
    unique_ptr<Coordinate[]> coor, resultCoor;
    for (const auto &combination : combinations) {
        temp = calculateReward(buffer, combination, &solutionTemp, width, height, matrix, seq, seqAmount, seqPointer.get(), coor);
        if (temp > max) {
            max = temp;
            solution = solutionTemp;
            resultCoor = move(coor);
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
