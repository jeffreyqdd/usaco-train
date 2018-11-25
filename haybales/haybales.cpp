#include <iostream>
#include <fstream>
using namespace std;

int kMaxPiles, pile_heights[10000]; 

int main(){
    int average = 0, move = 0;

    ifstream fin("haybales.in");
    ofstream fout("haybales.out");
    
    fin>>kMaxPiles;
    
    for(int i=0; i<kMaxPiles; i++){
        fin >> pile_heights[i];
        average += pile_heights[i];
    }
    average /= kMaxPiles;
    fin.close();

    //solving
    for(int i=0; i<kMaxPiles; i++){
        if(pile_heights[i] > average){
            move += pile_heights[i] - average;
        } 
    }

    fout << move << endl;

    return 0;
}