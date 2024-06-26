/*
Zach DeLong
EECS542
KUbe
*/
#include "cube.hpp"
#include <iostream>
#include <string>
#include <stdlib.h> 
#include <time.h> 
#include <fstream>
using namespace std;


//@brief: constructor
//@param: none
//@return: none
Cube::Cube(){}

//@brief: destructor
//@param: none
//@return: none
Cube::~Cube(){}

//@brief: creates a solved cube (used for testing)
//@param: none
//@return: none
void Cube::buildTest(){
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 9; j++){
            if((2 < i) && (i < 6) && (j < 3)){
                cube[i][j] = 'w';
            }
            else if((i < 3) && (2 < j)&& (j < 6)){
                cube[i][j] = 'o';
            }
            else if((2 < i) && (i < 6) && (2 < j) && (j < 6)){
                cube[i][j] = 'g';
            }
            else if((2 < i) && (i < 6) && (j > 5)){
                cube[i][j] = 'y';
            }
            else if((5 < i) && (i < 9) && (2 < j) && (j < 6)){
                cube[i][j] = 'r';
            }
            else if((i > 8) && (2 < j) && (j < 6)){
                cube[i][j] = 'b';
            }
            else{
                cube[i][j] = ' ';
            }
        }
    }

}

//@brief: used for generating a cube from input file
//@param: none
//@return: none
void Cube::buildCube(){
    fstream infile;
    infile.open("manual.txt");
    string line;
    for(int i = 0; i < 9; i++){
        getline(infile,line);
        for(int j = 0; j < 12; j++){
            cube[j][i] = line.at(j);
        }
    }
    infile.close();
}

/*
checks cube build:
-only 9 squares of each color
-only once center piece of each color
-all spaces have assigned value;
*/
bool Cube::checkBuild(){
    int count = 0;
    char colors[] = {'r', 'b', 'g', 'y', 'o', 'w'};
    for(char c : colors){
        for(int i = 0; i < 12; i++){
            for(int j = 0; j < 9; j++){
                if(cube[i][j] == c){
                    count++;
                }
            }
        }
        if(count != 9){
            cout<< "checkBuild error: invalid count on color char " + c;
        }
        count = 0;
    }
    count = 0;
    for(char c : colors){
        if(cube[1][4] == c)
            count++;
        if(cube[4][1] == c)
            count++;
        if(cube[4][4] == c)
            count++;
        if(cube[4][7] == c)
            count++;
        if(cube[7][4] == c)
            count++;
        if(cube[4][10] == c)
            count++;
        if(count > 1)
            cout << "checkBuild error: invalid center on color char " + c;
        count = 0;
    }
}

//@brief: selects a rotation function to call
//@param: char face: face to rotate
//@param: int num: number of rotations
//@return: none
void Cube::rotate(char face, int num){
    switch (face){
        case 'f':
            rotF(num);
            break;
        case 'b':
            rotB(num);
            break;
        case 'u':
            rotU(num);
            break;
        case 'r':
            rotR(num);
            break;
        case 'l':
            rotL(num);
            break;
        case 'd':
            rotD(num);
            break;
    }
}

//@brief: shifts array elements to simulate a rotation of the front face
//@param: int num: number of rotations
//@return: none
void Cube::rotF(int num){
    if(num == -1){
        num = 3;
         moves = moves + "f'/";
    }
    else{
        for(int i = 0; i < num; i++){
            moves = moves + "f/";
        }
    }
    for(int i = 0; i < num; i++){
    //front face shift
        //corners
        char temp1 = cube[3][3];
        cube[3][3] = cube[3][5];
        cube[3][5] = cube[5][5];
        cube[5][5] = cube[5][3];
        cube[5][3] = temp1;
        //edges
        temp1 = cube[3][4];
        cube[3][4] = cube[4][5];
        cube[4][5] = cube[5][4];
        cube[5][4] = cube[4][3];
        cube[4][3] = temp1;
    //LURD shift
        temp1 = cube[2][3];
        char temp2 = cube[2][4];
        char temp3 = cube[2][5];
        cube[2][3] = cube[3][6];
        cube[2][4] = cube[4][6];
        cube[2][5] = cube[5][6];
        cube[3][6] = cube[6][5];
        cube[4][6] = cube[6][4];
        cube[5][6] = cube[6][3];
        cube[6][5] = cube[5][2];
        cube[6][4] = cube[4][2];
        cube[6][3] = cube[3][2];
        cube[5][2] = temp1;
        cube[4][2] = temp2;
        cube[3][2] = temp3;
    }
}

//@brief: shifts array elements to simulate a rotation of the back face
//@param: int num: number of rotations
//@return: none
void Cube::rotB(int num){
    if(num == -1){
        num = 3;
         moves = moves + "b'/";
    }
    else{
        for(int i = 0; i < num; i++){
            moves = moves + "b/";
        }
    }
    for(int i = 0; i < num; i++){
    //back face shift
        //corners
        char temp1 = cube[9][3];
        cube[9][3] = cube[9][5];
        cube[9][5] = cube[11][5];
        cube[11][5] = cube[11][3];
        cube[11][3] = temp1;
        //edges
        temp1 = cube[9][4];
        cube[9][4] = cube[10][5];
        cube[10][5] = cube[11][4];
        cube[11][4] = cube[10][3];
        cube[10][3] = temp1;
    //RULD shift
        temp1 = cube[8][3];
        char temp2 = cube[8][4];
        char temp3 = cube[8][5];
        cube[8][3] = cube[5][8];
        cube[8][4] = cube[4][8];
        cube[8][5] = cube[3][8];
        cube[5][8] = cube[0][5];
        cube[4][8] = cube[0][4];
        cube[3][8] = cube[0][3];
        cube[0][5] = cube[3][0];
        cube[0][4] = cube[4][0];
        cube[0][3] = cube[5][0];
        cube[3][0] = temp1;
        cube[4][0] = temp2;
        cube[5][0] = temp3;
    }
}

//@brief: shifts array elements to simulate a rotation of the left face
//@param: int num: number of rotations
//@return: none
void Cube::rotL(int num){
    if(num == -1){
        num = 3;
         moves = moves + "l'/";
    }
    else{
        for(int i = 0; i < num; i++){
            moves = moves + "l/";
        }
    }
    for(int i = 0; i < num; i++){
    //left face shift
        //corners
        char temp1 = cube[0][3];
        cube[0][3] = cube[0][5];
        cube[0][5] = cube[2][5];
        cube[2][5] = cube[2][3];
        cube[2][3] = temp1;
        //edges
        temp1 = cube[0][4];
        cube[0][4] = cube[1][5];
        cube[1][5] = cube[2][4];
        cube[2][4] = cube[1][3];
        cube[1][3] = temp1;
    //BUFD shift
        temp1 = cube[11][3];
        char temp2 = cube[11][4];
        char temp3 = cube[11][5];
        cube[11][3] = cube[3][8];
        cube[11][4] = cube[3][7];
        cube[11][5] = cube[3][6];
        // cube[3][6] = cube[3][5];
        // cube[3][7] = cube[3][4];
        // cube[3][8] = cube[3][3];
        cube[3][6] = cube[3][3];
        cube[3][7] = cube[3][4];
        cube[3][8] = cube[3][5];
        cube[3][5] = cube[3][2];
        cube[3][4] = cube[3][1];
        cube[3][3] = cube[3][0];
        cube[3][2] = temp1;
        cube[3][1] = temp2;
        cube[3][0] = temp3;
    }
}

//@brief: shifts array elements to simulate a rotation of the right face
//@param: int num: number of rotations
//@return: none
void Cube::rotR(int num){
    if(num == -1){
        num = 3;
         moves = moves + "r'/";
    }
    else{
        for(int i = 0; i < num; i++){
            moves = moves + "r/";
        }
    }
    for(int i = 0; i < num; i++){
    //right face shift
        //corners
        char temp1 = cube[6][3];
        cube[6][3] = cube[6][5];
        cube[6][5] = cube[8][5];
        cube[8][5] = cube[8][3];
        cube[8][3] = temp1;
        //edges
        temp1 = cube[6][4];
        cube[6][4] = cube[7][5];
        cube[7][5] = cube[8][4];
        cube[8][4] = cube[7][3];
        cube[7][3] = temp1;
    //FUBD shift
        temp1 = cube[5][3];
        char temp2 = cube[5][4];
        char temp3 = cube[5][5];
        cube[5][3] = cube[5][6];
        cube[5][4] = cube[5][7];
        cube[5][5] = cube[5][8];
        cube[5][6] = cube[9][5];
        cube[5][7] = cube[9][4];
        cube[5][8] = cube[9][3];
        cube[9][5] = cube[5][0];
        cube[9][4] = cube[5][1];
        cube[9][3] = cube[5][2];
        cube[5][0] = temp1;
        cube[5][1] = temp2;
        cube[5][2] = temp3;
    }
}

//@brief: shifts array elements to simulate a rotation of the downward face
//@param: int num: number of rotations
//@return: none
void Cube::rotD(int num){
    if(num == -1){
        num = 3;
         moves = moves + "d'/";
    }
    else{
        for(int i = 0; i < num; i++){
            moves = moves + "d/";
        }
    }
    for(int i = 0; i < num; i++){
    //down face shift
        //corners
        char temp1 = cube[3][6];
        cube[3][6] = cube[3][8];
        cube[3][8] = cube[5][8];
        cube[5][8] = cube[5][6];
        cube[5][6] = temp1;
        //edges
        temp1 = cube[3][7];
        cube[3][7] = cube[4][8];
        cube[4][8] = cube[5][7];
        cube[5][7] = cube[4][6];
        cube[4][6] = temp1;
    //LFRB shift
        temp1 = cube[2][5];
        char temp2 = cube[1][5];
        char temp3 = cube[0][5];
        cube[2][5] = cube[11][5];
        cube[1][5] = cube[10][5];
        cube[0][5] = cube[9][5];
        cube[11][5] = cube[8][5];
        cube[10][5] = cube[7][5];
        cube[9][5] = cube[6][5];
        cube[8][5] = cube[5][5];
        cube[7][5] = cube[4][5];
        cube[6][5] = cube[3][5];
        cube[5][5] = temp1;
        cube[4][5] = temp2;
        cube[3][5] = temp3;
    }
}

//@brief: shifts array elements to simulate a rotation of the upper face
//@param: int num: number of rotations
//@return: none
void Cube::rotU(int num){
    if(num == -1){
        num = 3;
         moves = moves + "u'/";
    }
    else{
        for(int i = 0; i < num; i++){
            moves = moves + "u/";
        }
    }
    for(int i = 0; i < num; i++){
    //up face shift
        //corners
        char temp1 = cube[3][0];
        cube[3][0] = cube[3][2];
        cube[3][2] = cube[5][2];
        cube[5][2] = cube[5][0];
        cube[5][0] = temp1;
        //edges
        temp1 = cube[3][1];
        cube[3][1] = cube[4][2];
        cube[4][2] = cube[5][1];
        cube[5][1] = cube[4][0];
        cube[4][0] = temp1;
    //LBRF shift
        temp1 = cube[0][3];
        char temp2 = cube[1][3];
        char temp3 = cube[2][3];
        cube[0][3] = cube[3][3];
        cube[1][3] = cube[4][3];
        cube[2][3] = cube[5][3];
        cube[3][3] = cube[6][3];
        cube[4][3] = cube[7][3];
        cube[5][3] = cube[8][3];
        cube[6][3] = cube[9][3];
        cube[7][3] = cube[10][3];
        cube[8][3] = cube[11][3];
        cube[9][3] = temp1;
        cube[10][3] = temp2;
        cube[11][3] = temp3;
    }
}

//@brief: performance a right trigger move
//@param: int ref: used in slecting the appopriate face to perform trigger
//@return:none
void Cube::rightTrig(int ref){
    if(ref == 1){
        rotF(1);
        rotU(1);
        rotF(-1);
    }
    else if(ref == 4){
        rotR(1);
        rotU(1);
        rotR(-1);
    }
    else if(ref == 7){
        rotB(1);
        rotU(1);
        rotB(-1);
    }
    else if(ref == 10){
        rotL(1);
        rotU(1);
        rotL(-1);
    }
}

//@brief: performance a left trigger move
//@param: int ref: used in slecting the appopriate face to perform trigger
//@return:none
void Cube::leftTrig(int ref){
    if(ref == 1){
        rotB(-1);
        rotU(-1);
        rotB(1);
    }
    else if(ref == 4){
        rotL(-1);
        rotU(-1);
        rotL(1);
    }
    else if(ref == 7){
        rotF(-1);
        rotU(-1);
        rotF(1);
    }
    else if(ref == 10){
        rotR(-1);
        rotU(-1);
        rotR(1);
    }
}

//@brief: perform the furu algorithm used in the 4th step of solving
//@param: none
//@return: none
void Cube::furuAlg(){
    rotF(1);
    rotU(1);
    rotR(1);
    rotU(-1);
    rotR(-1);
    rotF(-1);
}

//@brief: perform the ruru algorithm used in the 5th step of solving
//@param: none
//@return: none
void Cube::ruruAlg(){
    rotR(1);
    rotU(1);
    rotR(-1);
    rotU(1);
    rotR(1);
    rotU(2);
    rotR(-1);
}

//@brief: perform the luru algorithm used in the 6th step of solving
//@param: int ref: represents the x coordinate of the reference face to perfrom the algorithm
//@return: none
void Cube::luruAlg(int ref){
    if(ref == 1){
        rotL(-1);
        rotU(1);
        rotR(1);
        rotU(-1);
        rotL(1);
        rotU(2);
        rotR(-1);
        rotU(1);
        rotR(1);
        rotU(2);
        rotR(-1);
    }
    else if(ref == 4){
        //l = f, r = b
        rotF(-1);
        rotU(1);
        rotB(1);
        rotU(-1);
        rotF(1);
        rotU(2);
        rotB(-1);
        rotU(1);
        rotB(1);
        rotU(2);
        rotB(-1);
    }
    else if(ref == 7){
        //l = r; r = l
        rotR(-1);
        rotU(1);
        rotL(1);
        rotU(-1);
        rotR(1);
        rotU(2);
        rotL(-1);
        rotU(1);
        rotL(1);
        rotU(2);
        rotL(-1);
    }
    else if(ref == 10){
        //l = b; r = f
        rotB(-1);
        rotU(1);
        rotF(1);
        rotU(-1);
        rotB(1);
        rotU(2);
        rotF(-1);
        rotU(1);
        rotF(1);
        rotU(2);
        rotF(-1);
    }
}

//@brief: perform the luru algorithm used in the 7th step of solving
//@param: int ref: represents the x coordinate of the reference face to perfrom the algorithm
//@return: none
void Cube::ffuAlg(int ref, char dir){
    if(ref == 10){
        if(dir == 'f'){
            rotF(2);
            rotU(1);
            rotR(-1);
            rotL(1);
            rotF(2);
            rotL(-1);
            rotR(1);
            rotU(1);
            rotF(2);
        }
        else{
            rotF(2);
            rotU(-1);
            rotR(-1);
            rotL(1);
            rotF(2);
            rotL(-1);
            rotR(1);
            rotU(-1);
            rotF(2);
        }
    }
    else if(ref == 1){
        //l = f, f = r, r = b 
        if(dir == 'f'){
            rotR(2);
            rotU(1);
            rotB(-1);
            rotF(1);
            rotR(2);
            rotF(-1);
            rotB(1);
            rotU(1);
            rotR(2);
        }
        else{
            rotR(2);
            rotU(-1);
            rotB(-1);
            rotF(1);
            rotR(2);
            rotF(-1);
            rotB(1);
            rotU(-1);
            rotR(2);
        }
    }
    else if(ref == 4){
        //r = l, l = r, f = b
        if(dir == 'f'){
            rotB(2);
            rotU(1);
            rotL(-1);
            rotR(1);
            rotB(2);
            rotR(-1);
            rotL(1);
            rotU(1);
            rotB(2);
        }
        else{
            rotB(2);
            rotU(-1);
            rotL(-1);
            rotR(1);
            rotB(2);
            rotR(-1);
            rotL(1);
            rotU(-1);
            rotB(2);
        }
    }
    else if(ref == 7){
        //r = f, l = b, f = l
        if(dir == 'f'){
            rotL(2);
            rotU(1);
            rotF(-1);
            rotB(1);
            rotL(2);
            rotB(-1);
            rotF(1);
            rotU(1);
            rotL(2);
        }
        else{
            rotL(2);
            rotU(-1);
            rotF(-1);
            rotB(1);
            rotL(2);
            rotB(-1);
            rotF(1);
            rotU(-1);
            rotL(2);
        }
    }
}

//@brief: prints the current state of the cube
//@param: none
//@return: none
void Cube::print(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 12; j++){
            cout << cube[j][i];
        }
        cout << "\n";
    }
    cout << "\n\n";
}

//@brief: returns the current string of moves
//@param: none
//@return: string moves
string Cube::getMoves(){
    return moves;
}

string Cube::getShuffle(){
    return shuffleMoves;
}

//@brief: returns the char representing the a color of a specified position
//@param: int x: x-coordindate possition
//@param: int y: y-coordindate possition
//@return: char representing a color
char Cube::getCube(int x, int y){
    return cube[x][y];
}

//@brief: shuffles the cube using random or predetermined moves
//@param: int c: 0 for predetermined moves, else perfom c random moves
//@return: none
void Cube::shuffle(int c){
    if(c == 0){
        rotF(2);
        rotR(2);
        rotB(2);
    }
    else{
        srand (time(NULL));
        for(int i = 0; i < c; i ++){
            int move = rand() % 10 + 1;
            if(move == 1){
                move = rand() % 10 + 1;
                if(move < 6){
                    rotU(1);
                }
                else{
                    rotU(-1);
                }
            }
            else if(move == 2){
                move = rand() % 10 + 1;
                if(move < 6){
                    rotD(1);
                }
                else{
                    rotD(-1);
                }
            }
            else if(move == 3){
                move = rand() % 10 + 1;
                if(move < 6){
                    rotL(1);
                }
                else{
                    rotL(-1);
                }
            }
            else if(move == 4){
                move = rand() % 10 + 1;
                if(move < 6){
                    rotR(1);
                }
                else{
                    rotR(-1);
                }
            }
            else if(move == 5){
                move = rand() % 10 + 1;
                if(move < 6){
                    rotB(1);
                }
                else{
                    rotB(-1);
                }
            }
            else if(move == 6){
                move = rand() % 10 + 1;
                if(move < 6){
                    rotU(1);
                }
                else{
                    rotU(-1);
                }
            }
        }
    }
    shuffleMoves = moves;
    moves = "";
}

