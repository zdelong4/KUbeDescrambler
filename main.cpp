/*
Zach DeLong
EECS542
KUbe
*/
#include <iostream>
#include "solver.hpp"
#include "cube.hpp"
#include <string>
using namespace std;

int main(){
    //take initial cube state and send to cube.cpp to build
    //send built cube to solver.cpp
    solver solution;
    string moves = solution.start();
    int count = 0;
    string moves_arr[moves.length()];
    int x = 0;
    for(int i = 0; i < moves.length()-1; i++){
        while(moves.at(i)!= '/'){
            moves_arr[x] += moves.at(i);
            i++;
            if(moves.at(i) == '/'){
                x++;
            } 
        }
    }
    for(int i = 1; i < moves.length()-1; i++){
        if((moves_arr[i-1] == "r")&&(moves_arr[i] == "r'")){
            moves_arr[i-1] = "";
            moves_arr[i] = "";
        }
        else if((moves_arr[i-1] == "r'")&&(moves_arr[i] == "r")){
            moves_arr[i-1] = "";
            moves_arr[i] = "";
        }
        else if((moves_arr[i-1] == "l")&&(moves_arr[i] == "l'")){
            moves_arr[i-1] = "";
            moves_arr[i] = "";
        }
        else if((moves_arr[i-1] == "l'")&&(moves_arr[i] == "l")){
            moves_arr[i-1] = "";
            moves_arr[i] = "";
        }
        else if((moves_arr[i-1] == "u")&&(moves_arr[i] == "u'")){
            moves_arr[i-1] = "";
            moves_arr[i] = "";
        }
        else if((moves_arr[i-1] == "u'")&&(moves_arr[i] == "u")){
            moves_arr[i-1] = "";
            moves_arr[i] = "";
        }
        else if((moves_arr[i-1] == "d")&&(moves_arr[i] == "d'")){
            moves_arr[i-1] = "";
            moves_arr[i] = "";
        }
        else if((moves_arr[i-1] == "d'")&&(moves_arr[i] == "d")){
            moves_arr[i-1] = "";
            moves_arr[i] = "";
        }
        else if((moves_arr[i-1] == "f")&&(moves_arr[i] == "f'")){
            moves_arr[i-1] = "";
            moves_arr[i] = "";
        }
        else if((moves_arr[i-1] == "f'")&&(moves_arr[i] == "f")){
            moves_arr[i-1] = "";
            moves_arr[i] = "";
        }
        else if((moves_arr[i-1] == "b")&&(moves_arr[i] == "b'")){
            moves_arr[i-1] = "";
            moves_arr[i] = "";
        }
        else if((moves_arr[i-1] == "b'")&&(moves_arr[i] == "b")){
            moves_arr[i-1] = "";
            moves_arr[i] = "";
        }
    }
    string moves_adj = "";
    for(int i  = 0; i < moves.length(); i++){
        if(moves_arr[i] != ""){
            count++;
            moves_adj = moves_adj + to_string(count) + moves_arr[i] + "/";
        }
    }
    cout << moves_adj + "\n\n";
    return(0);
}



