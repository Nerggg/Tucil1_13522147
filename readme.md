# Tugas Kecil Strategi Algoritma IF2211
## Completion of the Breach Protocol Minigame in Cyberpunk 2077 with the Brute Force Algorithm
## Table of Contents
  - [Table of Contents](#table-of-contents)
  - [General Information](#general-information)
  - [Contributor](#contributor)
  - [Technologies Used](#technologies-used)
  - [Features](#features)
  - [Structure](#structure)
  - [How to Use](#how-to-use)
    - [Dependencies](#dependencies)

## General Information
Breach Protocol is one of the minigames contained in the video game Cyberpunk 2077. This minigame presents code breaking and hacking challenges that allow players to hack security systems, access sensitive information, or take control of electronic devices in the game world.  
The brute force algorithm is a method of finding a solution by testing all possibilities sequentially until finding the correct solution. In the context of the Breach Protocol in the game Cyberpunk 2077, a brute force algorithm can be used to try every possible code combination successively until the correct code is found.

## Contributor
| Name | NIM |
|---|---|
| Ikhwan Al Hakim | 13522147 |

## Technologies Used
- C++

## Features
This program can solve a Breach Protocol minigame.  
There are two input modes in this program:  

1. Input from file  
Structure your input file like this:  
    ```
    buffer_size
    matrix_width matrix_height
    matrix
    number_of_sequences
    sequences_1
    sequences_1_reward
    sequences_2
    sequences_2_reward
    …
    sequences_n
    sequences_n_reward
    ```
    Then put it in the `input` directory  

2. Input from CLI  
If you choose this option, the matrix and sequences will be randomized.  
Just [run](#how-to-use) the program and it will tell you what to do next.

## Structure
```
├── bin
│   ├── linuxRun
│   └── windowsRun.exe
├── doc
│   └── Tucil1_K3_13522147_Ikhwan Al Hakim.pdf
├── readme.md
└── src
    ├── adt
    │   └── sequence.h
    ├── input
    │   ├── input1.txt
    │   ├── input2.txt
    │   ├── input3.txt
    │   └── input4.txt
    ├── io
    │   ├── io.cpp
    │   └── io.h
    ├── main.cpp
    └── output
        ├── cli1.txt
        ├── cli2.txt
        ├── cli3.txt
        ├── file1.txt
        ├── file2.txt
        ├── file3.txt
        └── file4.txt  
```

## How to Use
1. Clone this repository
    ```
    git clone https://github.com/Nerggg/Tucil1_13522147
    ```
2. Run the executable on the `bin` directory

### Dependencies
- C++ Compiler

Note: If you compile the code in the `src` directory, you have to move it to the `bin` directory in order for the IO functionality to work properly.
