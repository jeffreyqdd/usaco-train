#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

#define COWMAX 50000
#define NAMEMAX 20

int low[COWMAX];
int high[COWMAX];
string cow[COWMAX];

struct Name {
    string s;
    int index;
    bool is_reverse;
    bool operator<(Name const& o) const{
        if(s == o.s) return !is_reverse && o.is_reverse;
        return s<o.s;
    }   
};

Name names[COWMAX * 2];

void solve(int kTotalCow){
    for(int i=0; i<kTotalCow; i++){
        sort(cow[i].begin(), cow[i].end());

        names[2*i].s = cow[i];
        names[2*i].index = i;
        names[2*i].is_reverse = false;
    
        names[2*i+1].s = cow[i];
        reverse(names[2*i+1].s.begin(), names[2*i+1].s.end());
        names[2*i+1].index = i;
        names[2*i+1].is_reverse = true;
    }
    //names stand for the start address of the names array
    //names + (2 * kTotalCow), the (2 * kTotalCow) stands for the that many "addresses" down the "road"
    //in the this case, this stands for sorting the start to the final "actual" number
    sort(names, names + (2 * kTotalCow));

    //count all r-alpha words before every alpha word
    int low_cnt = 0;
    for(int i=0; i<kTotalCow*2; i++){
        if(names[i].is_reverse)
            low_cnt++;
        else{
            low[names[i].index] = low_cnt+1; //bc of 0 based indexing
        }
    }

    //vice versa, but start at end of array bc high counts counts for highest possible position.
    int high_cnt = 0;
    for(int i = kTotalCow*2 - 1; i>=0; i--){
        if(!names[i].is_reverse)
            high_cnt ++;
        else{
            high[names[i].index] = kTotalCow - high_cnt;//indexing has no effect here
        }
        
    }




    
}
int main(){
    ifstream fin("scramble.in");
    ofstream fout("scramble.out");

    int kTotalCow; fin >> kTotalCow;

    for(int i=0; i<kTotalCow; i++) fin >> cow[i];

    solve(kTotalCow);

    for (int i=0; i<kTotalCow; i++) fout << low[i] << " "<< high[i] << endl;

    return 0;
}