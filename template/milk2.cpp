/*
ID: jeffrey66
TASK: beads
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>


using namespace std;

struct cc {
    char color;
    int number;
};

int solve(string s){
    
    cc left = {' ', 0};
    cc right = {' ', 0};

    int whiteNum = 0;

    string beads = s + s;

    //for (auto i : beads) cout << i << " ";
    //cout << endl;

    int maxCnt = 0;


    for(int i = 0; i<s.length(); i++){
        char c = beads[i]; 
        
        if (c == 'w') whiteNum ++;
        else whiteNum = 0;
        
        if(c == right.color || c == 'w'){
            right.number++;
        }else{
            left = right;
            right = {c, 1};          
        }

        
        maxCnt = max(maxCnt, left.number+right.number);
    }

    return maxCnt;
}

int main(){

    ifstream fin("beads.in");
    ofstream fout("beads.out");

    int n;
    string s;

    fin >> n >> s;
    
    fout << solve(s) << endl;

    fin.close();
    fout.close();

    return 0;
}
