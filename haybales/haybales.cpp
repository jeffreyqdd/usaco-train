/*
ID: jeffrey66
TASK: haybales
LANG: C++
*/

#include <iostream>
#include <fstream>
using namespace std;

int kMaxPiles, pile_heights[10000]; 

int main(){
    ifstream fin("haybales.in");
    ofstream fout("haybales.out");
    
    fin>>kMaxPiles;
    
    int average = 0;
    for(int i=0; i<kMaxPiles; i++){
        int x; fin>>x;
        pile_heights[i] = x;
        average += x;
    }
    average /= kMaxPiles;
    fin.close();

    //solving
    int move = 0;
    for(int i=0; i<kMaxPiles; i++){
        if(pile_heights[i] > average){

            move += pile_heights[i] - average;
        } 

    }

    fout << move << endl;


    return 0;
}