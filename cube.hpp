/*
Zach DeLong
EECS542
KUbe
*/
#ifndef CUBE_HPP
#define CUBE_HPP
#include <iostream>
#include <string>
#include <stdlib.h> 
#include <time.h> 
using namespace std;


class Cube{
    private:
        char cube[12][9];
        string moves;
        string shuffleMoves;
    public:
        Cube();
        ~Cube();
        void buildCube();//builds cube, use for test cases
        bool checkBuild();
        char* getCube();
        char* getFace(char face);
        //cube and faces
        char refFace;
        
        //moves
        void rotate(char face, int num);
        void rotF(int num);
        void rotB(int num);
        void rotU(int num);
        void rotR(int num);
        void rotL(int num);
        void rotD(int num);
        void rightTrig(int ref);
        void leftTrig(int ref);
        void furuAlg();
        void ruruAlg();
        void luruAlg(int ref);
        void ffuAlg(int ref, char dir);
        void print();
        void buildTest();
        void updateFaces();
        string getMoves();
        string getShuffle();
        char getCube(int x, int y);
        void shuffle(int c);
        

    
};
#endif