#ifndef IO_H
#define IO_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "../adt/sequence.h"
using namespace std;

void readinput(int *buffer, int *width, int *height, string **matrix, Sequence **seq, int *seqAmount);

#endif