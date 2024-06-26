/*
Zach DeLong
EECS542
KUbe
*/
#ifndef SOLVER_HPP
#define SOLVER_HPP
#include <iostream>
#include <string>
#include "cube.hpp"
using namespace std;

class solver{
    private:
        Cube rubix;
    public:
        string start();
        string moves;
        char base;
        void daisy(int x, int y);
        void cross();
        void trigger(int x, int y);
        void topShift(int x, int y);
        void edgeSwap(int x, char up);
        bool replaceD();
        int findFace(int x);
        
        

};

#endif