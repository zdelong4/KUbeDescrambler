#include "cube.hpp"
#include <iostream>
#include <string>
using namespace std;

Cube::Cube(){}
Cube::~Cube(){}

//  Creates a solved cube
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

void Cube::buildCube(){
    //create test cases
    char cube[11][8]; 
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
             //fill every position in the fae arrays with r, b, w, y, o, g
            // do for each face
        }
    }

    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 9; j++){
            if((i < 3) && (j < 3)){
                cube[i][j] = ' ';
            }
            else if((i < 3) && (j > 5)){
                cube[i][j] = ' ';
            }
            else if((i > 5) && (j < 3))
                cube[i][j] = ' ';
        }
    }
}

/*
checks cube build for debugging:
-only 9 squares of each color
-only once center piece of each color
-all spaces have assigned value
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
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 9; j++){
            if((i < 3)&&(j < 3)){
                if(cube[i][j] != ' '){
                    cout<< "checkBuild error: color out of bounds";
                }
            }
            if((i < 3)&&(j < 3)){
                if(cube[i][j] != ' '){
                    cout<< "checkBuild error: color out of bounds";
                }
            }

        }
    }
}

// Calls a rotate face function based off char input and number of rotations
void Cube::rotate(char face, int num){
    switch (face){
        case 'f':
            rotF(num);
            break;
        case 'b':
            rotF(num);
            break;
        case 'u':
            rotF(num);
            break;
        case 'r':
            rotF(num);
            break;
        case 'l':
            rotF(num);
            break;
        case 'd':
            rotF(num);
            break;
    }
}

void Cube::rotF(int num){
    if(num == -1)
        num = 3;
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

void Cube::rotB(int num){
    if(num == -1)
        num = 3;
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

void Cube::rotL(int num){
    if(num == -1)
        num = 3;
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
        cube[11][3] = cube[3][6];
        cube[11][4] = cube[3][7];
        cube[11][5] = cube[3][8];
        cube[3][6] = cube[3][5];
        cube[3][7] = cube[3][4];
        cube[3][8] = cube[3][3];
        cube[3][5] = cube[3][2];
        cube[3][4] = cube[3][1];
        cube[3][3] = cube[3][0];
        cube[3][2] = temp1;
        cube[3][1] = temp2;
        cube[3][0] = temp3;
    }
}

void Cube::rotR(int num){
    if(num == -1)
        num = 3;
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

void Cube::rotD(int num){
    if(num == -1)
        num = 3;
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

void Cube::rotU(int num){
    if(num == -1)
        num = 3;
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

void Cube::print(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 12; j++){
            cout << cube[j][i];
        }
        cout << "\n";
    }
    cout << "\n\n";
}