#include "io.h"

void readinput(int *buffer, string **matrix, Sequence **seq) {    
    string temp;
    ifstream file ("../input/input1.txt");
    if (file.is_open()) {
        // dapetin buffer di baris pertama
        getline(file, temp);
        *buffer = stoi(temp);

        // dapetin ukuran matriks di baris kedua
        getline(file, temp);
        int i = 0;
        while (temp[i] != ' ') {
            i++;
        }
        int width = stoi(temp.substr(0,i));
        i++;
        int j = 0;
        while (temp[i+j] != '\0') {
            j++;
        }
        int height = stoi(temp.substr(i,j));

        // ngebaca matriksnya
        *matrix = new string[width*height];
        for (int y = 0; y < height; y++) {
        i = 0;
            getline(file, temp);
            for (int x = 0; x < width; x++) {
                (*matrix)[y * width + x] = temp.substr(i, 2);
                i += 3;
            }
        }

        // ngebaca sequence
        getline(file, temp);
        int seqAmount = stoi(temp);
        *seq = new Sequence[seqAmount];
        for (int i = 0; i < seqAmount; i++) {
            int seqSet = 1;
            j = 0;
            getline(file, temp);
            while (temp[j] != '\0') {
                if (temp[j] == ' ') {
                    seqSet++;
                }
                j++;
            }

            j = 0;
            (*seq)[i].set = new string[seqSet];
            for (int a = 0; a < seqSet; a++) {
                (*seq)[i].set[a] = temp.substr(j, 2);
                j += 3;
            }

            getline(file, temp);
            (*seq)[i].reward = stoi(temp);
        }

    }
}