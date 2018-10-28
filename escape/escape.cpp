/*
ID: jeffrey66
TASK: beads
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

/*
recursively iterate
TODO:
1.read file
2.recursively hasNoCarry cows
    - need a function to hasNoCarry carries;
*/
//globals

int cow, best = 0, w[20];
vector<int> subset;


bool hasNoCarry(int a, int b){
    for (; a> 0 && b> 0; a /= 10, b /= 10){
        if(a%10 + b%10 >= 10) return false;
    }
    return true;
}

//recursive iteration given cow#, sum of weights, # of cows on raft, total cows
void search(int k, int sum, int cnt, int n){

    best = max(best, cnt);

    if(k >= n) return;

    if(hasNoCarry(sum, w[k])) search(k+1, sum+w[k],cnt+1, n );

    search(k+1, sum,cnt, n );
    
}


int main(){
    ifstream fin("escape.in");
    ofstream fout("escape.out");
    fin>>cow;
    for(int i = 0; i<cow; i++){
        fin >> w[i];
    }
    fin.close();

    search(0,0,0,cow);

    fout << best << endl;
    fout.close();
    return 0;
}