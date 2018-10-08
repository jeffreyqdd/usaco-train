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
#include <algorithm>


using namespace std;

struct cc {
    char color;
    int number;
};

int solve(string s){
    
    cc left = {'X', 0};
    cc right = {'X', 0};



    string beads = s + s;

    //for (auto i : beads) cout << i << " ";
    //cout << endl;

    int maxCnt = 0;
    int whiteNum = 0;
    int overlapping = 0;

    for(int i = 0; i<s.length()*2; i++){
        char c = beads[i]; 
        
        if (c == 'w') whiteNum ++;
        
        if(c == right.color || c == 'w'){
            right.number++;
        }else{
            left = right;
            overlapping = whiteNum;
            right = {c, 1+overlapping};          
        }

        int total = left.number + right.number - overlapping;        
       
        maxCnt = max(maxCnt, total);

        if (c != 'w'){
            whiteNum = 0;
        }
    }

    return maxCnt;
}

int main(){

    ifstream fin("beads.in");
    ofstream fout("beads.out");

    int n;
    string s;

    fin >> n >> s;
    
    

    int r = solve(s);

    if (r > n) r = n;
    

    fout << r << endl;

    fin.close();
    fout.close();

    return 0;
}
