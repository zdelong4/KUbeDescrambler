/*
Zach DeLong
EECS542
KUbe
*/

/*
basics:
    -4 edges per face
        -edges have two colors
    -4 corners per face
        -corners have 3 colors
    -notation(turn the cube cockwise by 1 turn relative to someone looking at it)
        -F: Front face
        -B: Back face
        -L: Left face
        -R: Right face
        -D: Bottom face
        -U: Top face
        -_': rotate face 1 turn counterclockwise
    -algorithms:
        -FURU'R'F' (5)
        -RUR'URU2R' (6)
        -L'URU'LUR'RUR'URU2R' (7)
        -F2UR'LF2L'RUF2 (8)
        -F2U'R'LF2L'RU'F2 (8)

moves:
    -right trigger:
        -right face up
        -top face left(using right index)
        -right face down
    -left trigger:
        -left face up
        -top face right(using left index)
        -left face down

process:
    1. daisy
    2. make white cross
        -match edges with correct centers and turn twice 
    3. l/r triggers
        -match white corners with center pieces
        -use left trigger if on left side of center vice versa
    -unusual cases:
        -white corner on bottom face
            -use left/ right trigger to move to top face
        -white corner on top face
            -rotate until on opposite side of non-white corner on bottom
            -double right or left trigger to move to front race
            - solve with normal r/l trigger
    4. solving second layer
        -search top layer for edges without yellow
        -match edge piece with center
        -if top layer color of edge piece center on right
            -rotoate top left once, do right trigger
        -if on left
            -rotate top right once, do left trigger
        -replace white corner using right or left trigger from (3)
        -continue unil two layers are solver
        -if not two layers are not solved and top face have no edges without yellow
            -use right or left triggers to pull unsolved layer pieces out
    5. Create yellow cross on top of cube
        -if there are no yellow edge pieces
            -FURU'R'F'
        -two yellow edge peices that form a line with center
            -orient so line up and down
            -FURU'R'F'
        -two yellow edge peices that form backwards L
            -turn until edge peices are at 12 and 9
            -FURU'R'F'
    6. Solve yellow face
        -check how many yellow corners(0,1,2)
            -if 0 or 2
                -rotate top face until there is a yellow corner on the left face in top left
                -RUR'URU2R'
            -if 1
                -rotate yellow corner to bottom left
                -RUR'URU2R'
        -continue unil yellow is solved
    7. Position corners of yellow side
        -if no corners match center peices
            -L'URU'LUR'RUR'URU2R'
        -if one face has matching corner peices
            -hold that face in left hand
            -L'URU'LUR'RUR'URU2R'
    8. Position edges of yellow side
        -if one side is solved, face the solved side away from you
            -swap edges in clockwise
                -F2UR'LF2L'RUF2
            -swap edges in counterclockwise
                -
        -if no sides are solved
            -conterclockwise
                -F2U'R'LF2L'RU'F2 
            -reposition solved face away from you
            -counterclockwise
                -F2U'R'LF2L'RU'F2 
*/
#include "solver.hpp"
#include "cube.hpp"
#include <iostream>
#include <string>
using namespace std;


string solver::start(){
    char in;
    cout << "Enter Mode(t: test, m: manual): ";
    cin >> in;
    if(in == 'm'){
        rubix.buildCube();
    }
    else{
        rubix.buildTest();
        rubix.shuffle(0);
    }
    cout << "initial:\n";
    rubix.print();
    base = rubix.getCube(4,7);
    string moves;
    int x = -1;
    int y = -1;
    bool step1 = true;
    bool step2 = false;
    bool step3 = false;
    bool step4 = false;
    bool step5 = false;
    bool step6 = false;
    bool step7 = false;
    bool step8 = false;
    x = 0;
    while(step1){
        if((rubix.getCube(3,1) == base) && (rubix.getCube(4,0) == base) && (rubix.getCube(4,2) == base) && (rubix.getCube(5,1) == base)){
            //step1 complete
            step1 = false;
            cross();
            cout << "Step1 Complete:\n";
            rubix.print();
            step2 = true;
        }
        else{
            for(int i = 0; i < 12; i++){//traverse the center line
                if(rubix.getCube(i,4) == base){
                    daisy(i,4);
                }
            }
            if(rubix.getCube(3,7) == base){
                daisy(3,7);
            }
            if(rubix.getCube(5,7) == base){
                daisy(5,7);
            }
            for(int i = 3; i < 9; i++){
                if(rubix.getCube(4,i) == base){
                    daisy(4,i);
                }
            }
            if(rubix.getCube(1,3) == base){
                daisy(1, 3);
            }
            if(rubix.getCube(1,5) == base){
                daisy(1, 5);
            }
            if(rubix.getCube(7,3) == base){
                daisy(7, 3);
            }
            if(rubix.getCube(7,5) == base){
                daisy(7, 5);
            }
            if(rubix.getCube(10,3) == base){
                daisy(10, 3);
            }
            if(rubix.getCube(10,5) == base){
                daisy(10, 5);
            }
        }
    }

    bool hit = true;
    while(step2){
        hit = false;
        for(int i = 0; i < 12; i++){
            if(rubix.getCube(i,3) == base){
                hit = true;
                trigger(i, 3);
            }
        }
        if(hit == false){
            //check bottom layer
            if(rubix.getCube(0,5) == base){
                rubix.leftTrig(1);
            }
            else if(rubix.getCube(2,5) == base){
                rubix.rightTrig(1);
            }
            else if(rubix.getCube(3,5) == base){
                rubix.leftTrig(4);
            }
            else if(rubix.getCube(5,5) == base){
                rubix.rightTrig(4);
            }
            else if(rubix.getCube(6,5) == base){
                rubix.leftTrig(7);
            }
            else if(rubix.getCube(8,5) == base){
                rubix.rightTrig(7);
            }
            else if(rubix.getCube(9,5) == base){
                rubix.leftTrig(10);
            }
            else if(rubix.getCube(11,5) == base){
                rubix.rightTrig(10);
            }

            //check u face
            if(rubix.getCube(3,0) == base){
                topShift(3,0);
            }
            else if(rubix.getCube(3,2) == base){
                topShift(3,2);
            }
            else if(rubix.getCube(5,0) == base){
                topShift(5,0);
            }
            else if(rubix.getCube(5,2) == base){
                topShift(5,2);
            }
        }
        step2 = false;
        for(int i = 3; i < 6; i++){
            for(int j = 6; j < 9; j++){
                if(rubix.getCube(i,j) != base){
                    step2 = true;
                    break;
                }
            }
        }
    }
    cout << "Step2 Complete: \n";
    rubix.print();

    step3 = true;
    while(step3){
        //u face edges with no top color
        if((rubix.getCube(3,1) != rubix.getCube(4,1)) && (rubix.getCube(1,3) != rubix.getCube(4,1))){
                edgeSwap(1, rubix.getCube(3,1));
        }
        else if((rubix.getCube(4,0) != rubix.getCube(4,1)) && (rubix.getCube(10,3) != rubix.getCube(4,1))){
                edgeSwap(10, rubix.getCube(4,0));
        }
        else if((rubix.getCube(5,1) != rubix.getCube(4,1)) && (rubix.getCube(7,3) != rubix.getCube(4,1))){
                edgeSwap(7, rubix.getCube(5,1));
        }
        else if((rubix.getCube(4,2) != rubix.getCube(4,1)) && (rubix.getCube(4,3) != rubix.getCube(4,1))){
                edgeSwap(4, rubix.getCube(4,2));
        }
        else{
            for(int i = 0; i < 12; i++){
                if(i < 3){
                    if(rubix.getCube(i,4) != rubix.getCube(1,4)){
                        if(i == 0){
                            rubix.leftTrig(1);
                        }
                        else{
                            rubix.rightTrig(1);
                        }
                        i = 12;
                    }
                }
                else if(i < 6){
                    if(rubix.getCube(i,4) != rubix.getCube(4,4)){
                        if(i == 3){
                            rubix.leftTrig(4);
                        }
                        else{
                            rubix.rightTrig(4);
                        }
                        i = 12;
                    }
                }
                else if(i < 9){
                     if(rubix.getCube(i,4) != rubix.getCube(7,4)){
                        if(i == 6){
                            rubix.leftTrig(7);
                        }
                        else{
                            rubix.rightTrig(7);
                        }
                        i = 12;
                    }
                }
                else{
                    if(rubix.getCube(i,4) != rubix.getCube(10,4)){
                        if(i == 9){
                            rubix.leftTrig(10);
                        }
                        else{
                            rubix.rightTrig(10);
                        }
                        i = 12;
                    }
                }
            }
        }
        if(replaceD() == false){
            cout << "Step3 complete\n";
            rubix.print();
            step3 = false;
            step4 = true;
        }
    }
}

void solver::daisy(int x, int y){
    if(y == 3){//an edge peice cannot be two of the same color
        if(x == 1){
            rubix.rotate('l', 1);
            rubix.rotate('u', -1);
            rubix.rotate('f', 1);
        }
        else if(x == 4){
            rubix.rotate('f', 1);
            rubix.rotate('u', -1);
            rubix.rotate('r', 1);
        }
        else if(x == 7){
            rubix.rotate('r', 1);
            rubix.rotate('u', -1);
            rubix.rotate('b', 1);
        }
        else if(x == 10){
            rubix.rotate('b', 1);
            rubix.rotate('u', -1);
            rubix.rotate('l', 1);
        }
    }
    if(y == 4){
        if(x == 0){
            if(rubix.getCube(4,0) != rubix.getCube(x,y)){
                rubix.rotate('b', -1);
            }
            else if(rubix.getCube(3,1) != rubix.getCube(x,y)){
                rubix.rotate('u', 1);
                rubix.rotate('b', -1);
            }
            else if(rubix.getCube(4,2) != rubix.getCube(x,y)){
                rubix.rotate('u', 2);
                rubix.rotate('b', -1);
            }
            else if(rubix.getCube(5,1) != rubix.getCube(x,y)){
                rubix.rotate('u', -1);
                rubix.rotate('b', -1);
            }
        }
        else if(x == 2){
            if(rubix.getCube(4,2) != rubix.getCube(x,y)){
                rubix.rotate('f', 1);
            }
            else if(rubix.getCube(5,1) != rubix.getCube(x,y)){
                rubix.rotate('u', 1);
                rubix.rotate('f', 1);
            }
            else if(rubix.getCube(4,0) != rubix.getCube(x,y)){
                rubix.rotate('u', 2);
                rubix.rotate('f', 1);
            }
            else if(rubix.getCube(3,1) != rubix.getCube(x,y)){
                rubix.rotate('u', -1);
                rubix.rotate('f', 1);
            }
        }
        else if(x == 3){
            if(rubix.getCube(3,1) != rubix.getCube(x,y)){
                rubix.rotate('l', -1);
            }
            else if(rubix.getCube(4,2) != rubix.getCube(x,y)){
                rubix.rotate('u', 1);
                rubix.rotate('l', -1);
            }
            else if(rubix.getCube(5,1) != rubix.getCube(x,y)){
                rubix.rotate('u', 2);
                rubix.rotate('l', -1);
            }
            else if(rubix.getCube(4,0) != rubix.getCube(x,y)){
                rubix.rotate('u', -1);
                rubix.rotate('l', -1);
            }
        }
        else if(x == 5){
            if(rubix.getCube(5,1) != rubix.getCube(x,y)){
                rubix.rotate('r', 1);
            }
            else if(rubix.getCube(4,0) != rubix.getCube(x,y)){
                rubix.rotate('u', 1);
                rubix.rotate('r', 1);
            }
            else if(rubix.getCube(3,1) != rubix.getCube(x,y)){
                rubix.rotate('u', 2);
                rubix.rotate('r', 1);
            }
            else if(rubix.getCube(4,2) != rubix.getCube(x,y)){
                rubix.rotate('u', -1);
                rubix.rotate('r', 1);
            }
        }
        else if(x == 6){
            if(rubix.getCube(4,2) != rubix.getCube(x,y)){
                rubix.rotate('f', -1);
            }
            else if(rubix.getCube(5,1) != rubix.getCube(x,y)){
                rubix.rotate('u', 1);
                rubix.rotate('f', -1);
            }
            else if(rubix.getCube(4,0) != rubix.getCube(x,y)){
                rubix.rotate('u', 2);
                rubix.rotate('f', -1);
            }
            else if(rubix.getCube(3,1) != rubix.getCube(x,y)){
                rubix.rotate('u', -1);
                rubix.rotate('f', -1);
            }
        }
        else if(x == 8){
            if(rubix.getCube(4,0) != rubix.getCube(x,y)){
                rubix.rotate('b', 1);
            }
            else if(rubix.getCube(3,1) != rubix.getCube(x,y)){
                rubix.rotate('u', 1);
                rubix.rotate('b', 1);
            }
            else if(rubix.getCube(4,2) != rubix.getCube(x,y)){
                rubix.rotate('u', 2);
                rubix.rotate('b', 1);
            }
            else if(rubix.getCube(5,1) != rubix.getCube(x,y)){
                rubix.rotate('u', -1);
                rubix.rotate('b', 1);
            }
        }
        else if(x == 9){
            if(rubix.getCube(5,1) != rubix.getCube(x,y)){
                rubix.rotate('r', -1);
            }
            else if(rubix.getCube(4,0) != rubix.getCube(x,y)){
                rubix.rotate('u', 1);
                rubix.rotate('r', -1);
            }
            else if(rubix.getCube(3,1) != rubix.getCube(x,y)){
                rubix.rotate('u', 2);
                rubix.rotate('r', -1);
            }
            else if(rubix.getCube(4,2) != rubix.getCube(x,y)){
                rubix.rotate('u', -1);
                rubix.rotate('r', -1);
            }
        }
        else if(x == 11){
            if(rubix.getCube(3,1) != rubix.getCube(x,y)){
                rubix.rotate('l', 1);
            }
            else if(rubix.getCube(4,2) != rubix.getCube(x,y)){
                rubix.rotate('u', 1);
                rubix.rotate('l', 1);
            }
            else if(rubix.getCube(5,1) != rubix.getCube(x,y)){
                rubix.rotate('u', 2);
                rubix.rotate('l', 1);
            }
            else if(rubix.getCube(4,0) != rubix.getCube(x,y)){
                rubix.rotate('u', -1);
                rubix.rotate('l', 1);
            }
        }
    }
    else if(y == 5){
        if(x == 1){
            if(rubix.getCube(3,1) != rubix.getCube(x,y)){
                rubix.rotate('l', 1);
                rubix.rotate('u', 1);
                rubix.rotate('b', -1);
            }
            else if(rubix.getCube(4,2) != rubix.getCube(x,y)){
                rubix.rotate('u', 1);
                rubix.rotate('l', 1);
                rubix.rotate('u', 1);
                rubix.rotate('b', -1);
            }
            else if(rubix.getCube(5,1) != rubix.getCube(x,y)){
                rubix.rotate('u', 2);
                rubix.rotate('l', 1);
                rubix.rotate('u', 1);
                rubix.rotate('b', -1);
            }
            else if(rubix.getCube(4,0) != rubix.getCube(x,y)){
                rubix.rotate('u', -1);
                rubix.rotate('l', 1);
                rubix.rotate('u', 1);
                rubix.rotate('b', -1);
            }
        }
        else if(x == 4){
            if(rubix.getCube(4,2) != rubix.getCube(x,y)){
                rubix.rotate('f', 1);
                rubix.rotate('u', 1);
                rubix.rotate('l', -1);
            }
            else if(rubix.getCube(5,1) != rubix.getCube(x,y)){
                rubix.rotate('u', 1);
                rubix.rotate('f', 1);
                rubix.rotate('u', 1);
                rubix.rotate('l', -1);
            }
            else if(rubix.getCube(4,0) != rubix.getCube(x,y)){
                rubix.rotate('u', 2);
                rubix.rotate('f', 1);
                rubix.rotate('u', 1);
                rubix.rotate('l', -1);
            }
            else if(rubix.getCube(3,1) != rubix.getCube(x,y)){
                rubix.rotate('u', -1);
                rubix.rotate('f', 1);
                rubix.rotate('u', 1);
                rubix.rotate('l', -1);
            }
        }
        else if(x == 7){
            if(rubix.getCube(5,1) != rubix.getCube(x,y)){
                rubix.rotate('r', 1);
                rubix.rotate('u', 1);
                rubix.rotate('f', -1);
            }
            else if(rubix.getCube(4,0) != rubix.getCube(x,y)){
                rubix.rotate('u', 1);
                rubix.rotate('r', 1);
                rubix.rotate('u', 1);
                rubix.rotate('f', -1);
            }
            else if(rubix.getCube(3,1) != rubix.getCube(x,y)){
                rubix.rotate('u', 2);
                rubix.rotate('r', 1);
                rubix.rotate('u', 1);
                rubix.rotate('f', -1);
            }
            else if(rubix.getCube(4,2) != rubix.getCube(x,y)){
                rubix.rotate('u', -1);
                rubix.rotate('r', 1);
                rubix.rotate('u', 1);
                rubix.rotate('f', -1);
            }
        }
        else if(x == 10){
            if(rubix.getCube(4,0) != rubix.getCube(x,y)){
                rubix.rotate('b', 1);
                rubix.rotate('u', 1);
                rubix.rotate('r', -1);
            }
            else if(rubix.getCube(3,1) != rubix.getCube(x,y)){
                rubix.rotate('u', 1);
                rubix.rotate('b', 1);
                rubix.rotate('u', 1);
                rubix.rotate('r', -1);
            }
            else if(rubix.getCube(4,2) != rubix.getCube(x,y)){
                rubix.rotate('u', 2);
                rubix.rotate('b', 1);
                rubix.rotate('u', 1);
                rubix.rotate('r', -1);
            }
            else if(rubix.getCube(5,1) != rubix.getCube(x,y)){
                rubix.rotate('u', -1);
                rubix.rotate('b', 1);
                rubix.rotate('u', 1);
                rubix.rotate('r', -1);
            }
        }
    }
    else if(y == 6){
        if(x == 4){
            if(rubix.getCube(5,1) != rubix.getCube(x,y)){
                rubix.rotate('d', 1);
                rubix.rotate('r', 2);
            }
            else if(rubix.getCube(4,0) != rubix.getCube(x,y)){
                rubix.rotate('u', 1);
                rubix.rotate('d', 1);
                rubix.rotate('r', 2);
            }
            else if(rubix.getCube(3,1) != rubix.getCube(x,y)){
                rubix.rotate('u', 2);
                rubix.rotate('d', 1);
                rubix.rotate('r', 2);
            }
            else if(rubix.getCube(4,2) != rubix.getCube(x,y)){
                rubix.rotate('u', -1);
                rubix.rotate('d', 1);
                rubix.rotate('r', 2);
            }
        }
    }
    else if(y == 7){
        if(x == 3){
            if(rubix.getCube(3,1) != rubix.getCube(x,y)){
                rubix.rotate('l', 2);
            }
            else if(rubix.getCube(4,2) != rubix.getCube(x,y)){
                rubix.rotate('u', 1);
                rubix.rotate('l', 2);
            }
            else if(rubix.getCube(5,1) != rubix.getCube(x,y)){
                rubix.rotate('u', 2);
                rubix.rotate('l', 2);
            }
            else if(rubix.getCube(4,0) != rubix.getCube(x,y)){
                rubix.rotate('u', -1);
                rubix.rotate('l', 2);
            }
        }
        if(x == 5){
            if(rubix.getCube(5,1) != rubix.getCube(x,y)){
                rubix.rotate('r', 2);
            }
            else if(rubix.getCube(4,0) != rubix.getCube(x,y)){
                rubix.rotate('u', 1);
                rubix.rotate('r', 2);
            }
            else if(rubix.getCube(3,1) != rubix.getCube(x,y)){
                rubix.rotate('u', 2);
                rubix.rotate('r', 2);
            }
            else if(rubix.getCube(4,2) != rubix.getCube(x,y)){
                rubix.rotate('u', -1);
                rubix.rotate('r', 2);
            }
        }
    }
    else if(y == 8){
        if(x == 4){
            if(rubix.getCube(5,1) != rubix.getCube(x,y)){
                rubix.rotate('d', 1);
                rubix.rotate('l', 2);
            }
            else if(rubix.getCube(4,0) != rubix.getCube(x,y)){
                rubix.rotate('u', 1);
                rubix.rotate('d', 1);
                rubix.rotate('l', 2);
            }
            else if(rubix.getCube(3,1) != rubix.getCube(x,y)){
                rubix.rotate('u', 2);
                rubix.rotate('d', 1);
                rubix.rotate('l', 2);
            }
            else if(rubix.getCube(4,2) != rubix.getCube(x,y)){
                rubix.rotate('u', -1);
                rubix.rotate('d', 1);
                rubix.rotate('l', 2);
            }
        }
    }
}

void solver::trigger(int x, int y){
    int refCoord = -1;
    char refChar;
    char trig;
    if(x == 11){
        refCoord = 0;
        trig = 'l';
    }
    else if(x == 0){
        refCoord = 11;
        trig = 'r';
    }
    else if((x == 2)||(x==5)||(x==8)){
        refCoord = x + 1;
        trig = 'l';
    }
    else{
        refCoord = x - 1;
        trig = 'r';
    }
    refChar = rubix.getCube(refCoord,y);
    if(refChar == rubix.getCube(1,4)){
        if((refCoord == 3)||(refCoord == 5)){
            rubix.rotate('u', 1);
        }
        else if((refCoord == 6)||(refCoord == 8)){
            rubix.rotate('u', 2);
        }
        else if((refCoord == 9)||(refCoord == 11)){
            rubix.rotate('u', -1);
        }
        refCoord = 1;
    }
    else if(refChar == rubix.getCube(4,4)){
        if((refCoord == 6)||(refCoord == 8)){
            rubix.rotate('u', 1);
        }
        else if((refCoord == 9)||(refCoord == 11)){
            rubix.rotate('u', 2);
        }
        else if((refCoord == 0)||(refCoord == 2)){
            rubix.rotate('u', -1);
        }
        refCoord = 4;
    }
    else if(refChar == rubix.getCube(7,4)){
        if((refCoord == 9)||(refCoord == 11)){
            rubix.rotate('u', 1);
        }
        else if((refCoord == 0)||(refCoord == 2)){
            rubix.rotate('u', 2);
        }
        else if((refCoord == 3)||(refCoord == 5)){
            rubix.rotate('u', -1);
        }
        refCoord = 7;
    }
    else if(refChar == rubix.getCube(10,4)){
        if((refCoord == 0)||(refCoord == 2)){
            rubix.rotate('u', 1);
        }
        else if((refCoord == 3)||(refCoord == 5)){
            rubix.rotate('u', 2);
        }
        else if((refCoord == 6)||(refCoord == 8)){
            rubix.rotate('u', -1);
        }
        refCoord = 10;
    }
    if(trig == 'l'){
        rubix.leftTrig(refCoord);
    }
    else{
        rubix.rightTrig(refCoord);
    }
}

void solver::topShift(int x, int y){
    if((x == 3) && (y == 0)){
        if(rubix.getCube(3,8) != base){
            rubix.leftTrig(1);
            rubix.leftTrig(1);
        }
        else if(rubix.getCube(3,6) != base){
            rubix.rotate('u', -1);
            rubix.leftTrig(4);
            rubix.leftTrig(4);
        }
        else if(rubix.getCube(5,8) != base){
            rubix.rotate('u', 1);
            rubix.rightTrig(7);
            rubix.rightTrig(7);
        }
        else if(rubix.getCube(5,6) != base){
            rubix.rotate('u', 2);
            rubix.rightTrig(4);
            rubix.rightTrig(4);
        }
    }
    else if((x == 3) && (y == 2)){
        if(rubix.getCube(3,6) != base){
            rubix.leftTrig(4);
            rubix.leftTrig(4);
        }
        else if(rubix.getCube(3,8) != base){
            rubix.rotate('u', 1);
            rubix.leftTrig(1);
            rubix.leftTrig(1);
        }
        else if(rubix.getCube(5,8) != base){
            rubix.rotate('u', 2);
            rubix.rightTrig(7);
            rubix.rightTrig(7);
        }
        else if(rubix.getCube(5,6) != base){
            rubix.rotate('u', -1);
            rubix.rightTrig(4);
            rubix.rightTrig(4);
        }
    }
    else if((x == 5) && (y == 0)){
        if(rubix.getCube(5,8) != base){
            rubix.rightTrig(7);
            rubix.rightTrig(7);
        }
        else if(rubix.getCube(5,6) != base){
            rubix.rotate('u', 1);
            rubix.rightTrig(4);
            rubix.rightTrig(4);
        }
        else if(rubix.getCube(3,6) != base){
            rubix.rotate('u', 2);
            rubix.leftTrig(4);
            rubix.leftTrig(4);
        }
        else if(rubix.getCube(3,8) != base){
            rubix.rotate('u', -1);
            rubix.leftTrig(1);
            rubix.leftTrig(1);
        }
    }
    else if((x == 5) && (y == 2)){
        if(rubix.getCube(5,6) != base){
            rubix.rightTrig(4);
            rubix.rightTrig(4);
        }
        else if(rubix.getCube(5,8) != base){
            rubix.rotate('u', -1);
            rubix.rightTrig(7);
            rubix.rightTrig(7);
        }
        else if(rubix.getCube(3,6) != base){
            rubix.rotate('u', 1);
            rubix.leftTrig(4);
            rubix.leftTrig(4);
        }
        else if(rubix.getCube(3,8) != base){
            rubix.rotate('u', 2);
            rubix.leftTrig(1);
            rubix.leftTrig(1);
        }
    }
}

void solver::edgeSwap(int x, char up){
    x = findFace(x);
    if(x == 1){
        if(up == rubix.getCube(4,4)){
            rubix.rotate('u', 1);
            rubix.rightTrig(1);
        }
        else{
            rubix.rotate('u', -1);
            rubix.leftTrig(1);
        }
    }
    else if(x == 4){
        if(up == rubix.getCube(7,4)){
            rubix.rotate('u', 1);
            rubix.rightTrig(4);
        }
        else{
            rubix.rotate('u', -1);
            rubix.leftTrig(4);
        }
    }
    else if(x == 7){
        if(up == rubix.getCube(10,4)){
            rubix.rotate('u', 1);
            rubix.rightTrig(7);
        }
        else{
            rubix.rotate('u', -1);
            rubix.leftTrig(7);
        }
    }
    else if(x == 10){
        if(up == rubix.getCube(1,4)){
            rubix.rotate('u', 1);
            rubix.rightTrig(10);
        }
        else{
            rubix.rotate('u', -1);
            rubix.leftTrig(10);
        }
    }
}

int solver::findFace(int x){
    int numRot = 0;
    char target = rubix.getCube(x,3);
    if(x == 0){
        x = 1;
    }
    if(target == rubix.getCube(1,4)){
        if(x == 4){
            rubix.rotate('u', 1);
        }
        else if(x == 7){
            rubix.rotate('u', 2);
        }
        else if(x == 10){
            rubix.rotate('u', -1);
        }
        x = 1;
    }
    else if(target == rubix.getCube(4,4)){
       if(x == 1){
            rubix.rotate('u', -1);
        }
        else if(x == 7){
            rubix.rotate('u', 1);
        }
        else if(x == 10){
            rubix.rotate('u', 2);
        }
        x = 4;
    }
    else if(target == rubix.getCube(7,4)){
        if(x == 1){
            rubix.rotate('u', 2);
        }
        else if(x == 4){
            rubix.rotate('u', -1);
        }
        else if(x == 10){
            rubix.rotate('u', 1);
        }
        x = 7;
    }
    else if(target == rubix.getCube(10,4)){
        if(x == 1){
            rubix.rotate('u', 1);
        }
        else if(x == 4){
            rubix.rotate('u', 2);
        }
        else if(x == 7){
            rubix.rotate('u', -1);
        }
        x = 10;
    }
    return x;
}

bool solver::replaceD(){
    bool rep = false;
    for(int i = 0; i < 12; i++){
        if(rubix.getCube(i,3) == base){
            trigger(i,3);
            rep = true;
        }
    }
    return rep; 
}