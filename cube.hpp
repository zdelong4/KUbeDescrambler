#ifndef CUBE_HPP
#define CUBE_HPP
#include <iostream>

/// Creates 12 by 9 array of character representing a 3 by 3 rubiks cube
/// and defines face rotations

class Cube{
    private:
       char cube[12][9];

    public:
        Cube();
        ~Cube();
    
        //builds cube, use for test cases
        void buildCube();
        bool checkBuild();
        
        char* getCube();
        char* getFace(char face);

        //cube and faces
        char f_face[2][2];
        char b_face[2][2];
        char u_face[2][2];
        char r_face[2][2];
        char l_face[2][2];
        char d_face[2][2];
        char refFace;

        //moves
        void rotate(char face, int num);
        void rotF(int num);
        void rotB(int num);
        void rotU(int num);
        void rotR(int num);
        void rotL(int num);
        void rotD(int num);
        void rightTrig();
        void leftTrig();
        void furuAlg();
        void ruruAlg();
        void luruAlg();
        void print();
        void buildTest();

    
};
#endif