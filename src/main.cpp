#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <memory>
#include "io/io.h"
using namespace std;

bool turnCheck(int buffer, vector<pair<int, int>> input) {
    for (int i = 1; i < buffer; i++) {
        if (i % 2 != 0) {
            if (input[i].second != input[i-1].second || input[i].first == input[i-1].first) {
                return false;
            }
        }
        else if (i % 2 == 0) {
            if (input[i].first != input[i-1].first || input[i].second == input[i-1].second) {
                return false;
            }
        }
    }

    if (input[0].first != 0) {
        return false;
    }

    return true;
}

bool checkDone(int *seqPointer, Sequence *seq, int idx) {
    return seqPointer[idx] == (seq[idx].length);
}

int calculateReward(int buffer, vector<pair<int, int>> input, int width, int height, string *matrix, Sequence *seq, int seqAmount, int *seqPointer) {
    bool valid = turnCheck(buffer, input);

    if (!valid) {
        return 0;
    }

    int result = 0;
    for (int i = 0; i < buffer; i++) {
        for (int a = 0; a < seqAmount; a++) {            
            if (matrix[input[i].first * width + input[i].second] == seq[a].set[seqPointer[a]]) {
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
                // cout << "current sequence ";
                // for (int i = 0; i < buffer; i++) {
                //     cout << matrix[input[i].first * width + input[i].second] << " ";
                // } 
                // cout << endl << endl;
            }
        }
    }

    // debug begin
    // if (coor[0].x == 0 && coor[0].y == 0 && coor[1].x == 0 && coor[1].y == 3 && coor[2].x == 2 && coor[2].y == 3 && coor[3].x == 2 && coor[3].y == 4 && coor[4].x == 5 && coor[4].y == 4 && coor[5].x == 5 && coor[5].y == 3 && coor[6].x == 4 && coor[6].y == 3) {
    // if (coor[0].x == 0 && coor[0].y == 0 && coor[1].x == 0 && coor[1].y == 3) {
    //     cout << input << endl;
    // }
    // debug end
    for (int i = 0; i < seqAmount; i++) {
        seqPointer[i] = 0;
    }

    return result;
}

vector<vector<pair<int, int>>> generateCombinations(int width, int height, int buffer_size, pair<int, int> start={0,0}, bool is_horizontal=true) {
    int i = start.first;
    int j = start.second;

    vector<vector<int>> matrix(height, vector<int>(width));

    // Fill the matrix with values using nested loops
    int count = 1;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            matrix[i][j] = count++;
        }
    }
    
    if (buffer_size == 1) {
        if (is_horizontal) {
            vector<vector<pair<int, int>>> paths;
            for (int new_j = 0; new_j < matrix[0].size(); ++new_j) {
                if (new_j != j) {
                    paths.push_back({{i, new_j}});
                }
            }
            return paths;
        } else {
            vector<vector<pair<int, int>>> paths;
            for (int new_i = 0; new_i < matrix.size(); ++new_i) {
                if (new_i != i) {
                    paths.push_back({{new_i, j}});
                }
            }
            return paths;
        }
    } else {
        vector<vector<pair<int, int>>> paths;
        if (is_horizontal) {
            for (int new_j = 0; new_j < matrix[0].size(); ++new_j) {
                if (new_j != j) {
                    auto smaller_paths = generateCombinations(width, height, buffer_size - 1, {i, new_j}, false);
                    for (auto path : smaller_paths) {
                        path.insert(path.begin(), {i, new_j});
                        paths.push_back(path);
                    }
                }
            }
        } else {
            for (int new_i = 0; new_i < matrix.size(); ++new_i) {
                if (new_i != i) {
                    auto smaller_paths = generateCombinations(width, height, buffer_size - 1, {new_i, j}, true);
                    for (auto path : smaller_paths) {
                        path.insert(path.begin(), {new_i, j});
                        paths.push_back(path);
                    }
                }
            }
        }
        return paths;
    }
}

void fileOption() {
    string filename;
    cout << "Enter the file name (without format): ";
    cin >> filename;
    int buffer, width, height, seqAmount;
    string *matrix;
    Sequence *seq;
    readinput(filename, &buffer, &width, &height, &matrix, &seq, &seqAmount);

    unique_ptr<int[]> seqPointer(new int[seqAmount]);
    for (int i = 0; i < seqAmount; i++) {
        seqPointer[i] = 0;
    }
 
    clock_t start = clock();

    vector<vector<pair<int, int>>> combinations = generateCombinations(width, height, buffer);
    
    int max = 0, temp;
    vector<pair<int, int>> resultCoor;
    for (const auto &combination : combinations) {
        temp = calculateReward(buffer, combination, width, height, matrix, seq, seqAmount, seqPointer.get());
        if (temp > max) {
            max = temp;
            resultCoor = combination;
        }
    }

    clock_t stop = clock();
    double timeTaken = (double)(stop - start) / CLOCKS_PER_SEC;
    cout << endl << "Done!" << endl;
    cout << "Time taken: " << timeTaken * 1000 << " ms" << endl;
    cout << "Max value: " << max << endl;

    if (max == 0) {
        cout << "There is no buffer solution because the max value is 0." << endl;
    }
    else {
        cout << "Buffer solution: ";
        for (int i = 0; i < buffer; i++) {
            cout << matrix[resultCoor[i].first * width + resultCoor[i].second] << " ";
        } 
        cout << endl;
        cout << "Buffer solution's coordinate: ";
        for (int i = 0; i < buffer; i++) {
            cout << "(" << resultCoor[i].second << "," << resultCoor[i].first << ") ";   
        }
        cout << endl;
    }
    cout << endl;

    char yOrN;
    cout << "Do you want to save the solution into a file? (Y/N)" << endl;
    cin >> yOrN;
    if (yOrN == 'Y' || yOrN == 'y') {
        cout << "Enter the filename (without format): ";
        cin >> filename;
        saveToFile(filename, buffer, height, width, matrix, seqAmount, seq, timeTaken, max, resultCoor);
    }
}

void cliOption() {
    int n, buffer, width, height, seqAmount, intTemp;
    vector<string> token;
    string strTemp;
    cout << "Enter the number of token types: ";
    cin >> n;
    cout << "Enter the tokens:\nNote: The length must be 2." << endl;
    for (int i = 0; i < n; i++) {
        cin >> strTemp;
        token.push_back(strTemp);
    }
    cout << "Enter the buffer size: ";
    cin >> buffer;
    cout << "Enter the matrix's width: ";
    cin >> width;
    cout << "Enter the matrix's height: ";
    cin >> height;
    cout << "Enter the amount of sequences: ";
    cin >> seqAmount;
    cout << "Enter the maximum length of the sequence: ";
    cin >> n;

    srand(time(0));
    string* matrix = new string[width * height];
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int randomIndex = rand() % token.size();
            matrix[i * width + j] = token[randomIndex];
        }
    }

    Sequence *seq = new Sequence[seqAmount];
    for (int i = 0; i < seqAmount; i++) {
        int randomLength = 1 + rand() % n;
        int randomReward = 1 + rand() % 100;
        seq[i].set = new string[randomLength];
        for (int j = 0; j < randomLength; j++) {
            int randomIndex = rand() % token.size();
            seq[i].set[j] = token[randomIndex];
        }
        seq[i].reward = randomReward;
        seq[i].length = randomLength;
    }

    cout << endl << "Generated Matrix:" << endl;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cout << matrix[i * width + j] << " ";
        }
        cout << endl;
    }

    cout << endl << "Generated sequence:" << endl;
    for (int i = 0; i < seqAmount; i++) {
        for (int j = 0; j < seq[i].length; j++) {
            cout << seq[i].set[j] << " ";
        }
        cout << endl << "Reward: " << seq[i].reward << endl;
    }

    unique_ptr<int[]> seqPointer(new int[seqAmount]);
    for (int i = 0; i < seqAmount; i++) {
        seqPointer[i] = 0;
    }
 
    clock_t start = clock();

    vector<vector<pair<int, int>>> combinations = generateCombinations(width, height, buffer);
    
    int max = 0, temp;
    vector<pair<int, int>> resultCoor;
    for (const auto &combination : combinations) {
        temp = calculateReward(buffer, combination, width, height, matrix, seq, seqAmount, seqPointer.get());
        if (temp > max) {
            max = temp;
            resultCoor = combination;
        }
    }

    clock_t stop = clock();
    double timeTaken = (double)(stop - start) / CLOCKS_PER_SEC;
    cout << endl << "Done!" << endl;
    cout << "Time taken: " << timeTaken * 1000 << " ms" << endl;
    cout << "Max value: " << max << endl;

    if (max == 0) {
        cout << "There is no buffer solution because the max value is 0." << endl;
    }
    else {
        cout << "Buffer solution: ";
        for (int i = 0; i < buffer; i++) {
            cout << matrix[resultCoor[i].first * width + resultCoor[i].second] << " ";
        } 
        cout << endl;
        cout << "Buffer solution's coordinate: ";
        for (int i = 0; i < buffer; i++) {
            cout << "(" << resultCoor[i].second << "," << resultCoor[i].first << ") ";   
        }
        cout << endl;
    }    
    cout << endl;

    char yOrN;
    cout << "Do you want to save the solution into a file? (Y/N)" << endl;
    cin >> yOrN;
    if (yOrN == 'Y' || yOrN == 'y') {
        string filename;
        cout << "Enter the filename (without format): ";
        cin >> filename;
        saveToFile(filename, buffer, height, width, matrix, seqAmount, seq, timeTaken, max, resultCoor);
    }
}

int main() {
    int opt;
    cout << "Welcome to Cyberpunk Breach Protocol Hacker!" << endl;
    cout << "Choose the input option:" << endl;
    cout << "[1] Input from file (put the file in src/input)" << endl;
    cout << "[2] Input from CLI (the matrix and the sequence will be randomized)" << endl;
    cin >> opt;

    if (opt == 1) {
        fileOption();
    }
    else if (opt == 2) {
        cliOption();
    }
}
