#include "io.h"

void readinput(string filename, int *buffer, int *width, int *height, string **matrix, Sequence **seq, int *seqAmount) {    
    string temp;
    ifstream file ("./input/" + filename + ".txt");
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
        *width = stoi(temp.substr(0,i));
        i++;
        int j = 0;
        while (temp[i+j] != '\0') {
            j++;
        }
        *height = stoi(temp.substr(i,j));

        // ngebaca matriksnya
        *matrix = new string[*width*(*height)];
        for (int y = 0; y < *height; y++) {
        i = 0;
            getline(file, temp);
            for (int x = 0; x < *width; x++) {
                (*matrix)[y * (*width) + x] = temp.substr(i, 2);
                i += 3;
            }
        }

        // ngebaca sequence
        getline(file, temp);
        *seqAmount = stoi(temp);
        *seq = new Sequence[*seqAmount];
        for (int i = 0; i < *seqAmount; i++) {
            int seqSet = 1;
            j = 0;
            getline(file, temp);
            while (temp[j] != '\0') {
                if (temp[j] == ' ') {
                    seqSet++;
                }
                j++;
            }

            (*seq)[i].length = seqSet;
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

void saveToFile(string filename, int buffer, int height, int width, string *matrix, int seqAmount, Sequence *seq, double timeTaken, int reward, vector<pair<int, int>> coor) {
    ofstream file ("./output/" + filename + ".txt");
    if (file.is_open()) {
        file << "Matrix:" << endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                file << matrix[i * width + j] << " ";
            }
            file << endl;
        }
        file << endl;

        file << "Sequences:" << endl;
        for (int i = 0; i < seqAmount; i++) {
            for (int j = 0; j < seq[i].length; j++) {
                file << seq[i].set[j] << " ";
            }
            file << endl;
            file << "Reward: " << seq[i].reward;
            file << endl;
        }
        file << endl;

        file << "Time taken: " << timeTaken * 1000 << " ms" << endl;
        file << "Max value: " << reward << endl;
        file << "Buffer solution: ";
        for (int i = 0; i < buffer; i++) {
            file << matrix[coor[i].first * width + coor[i].second] << " ";
        } 
        file << endl;
        file << "Buffer solution's coordinate: ";
        for (int i = 0; i < buffer; i++) {
            file << "(" << coor[i].second << "," << coor[i].first << ") ";   
        }
        file << endl;
    }
}