#ifndef IO_H
#define IO_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "../adt/sequence.h"
using namespace std;

void readinput(string filename, int *buffer, int *width, int *height, string **matrix, Sequence **seq, int *seqAmount);
void saveToFile(string filename, int buffer, int height, int width, string *matrix, int seqAmount, Sequence *seq, double timeTaken, int reward, vector<pair<int, int>> coor);

#endif