#include <iostream>
#include <fstream>
#include <string>
#include "io/io.h"
using namespace std;

int main() {
    int buffer;
    string *matrix;
    Sequence *seq;
    readinput(&buffer, &matrix, &seq);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            cout << matrix[i * 6 + j] << " ";
        }
        cout << endl;
    }
}