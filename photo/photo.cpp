/*
ID: jeffrey66
TASK: beads
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

/*
Given: Total number of cows with ids [1,N] .. line 1
and 5 "photos" depi cting the order of the cows(N*5) .. line N*5 + 1

Solve:
-sort based on how often two numebrs appear next to each other
*/


int kTotalCow;
map<int,int> position[5];
vector<int> cow_order;

bool comp(int a, int b){
    int count = 0;
    for(int photo=0; photo<5; photo++){
        if(position[photo][a] < position[photo][b]) count++;
    }
    return count > 2;
}


int main(){
    //read
    ifstream fin("photo.in");
    ofstream fout("photo.out");

    fin >> kTotalCow;
    
    for(int photo=0; photo<5; photo++){
        for(int index=0; index<kTotalCow; index++){
            int id; fin>>id;
            position[photo][id] = index;
            if(photo==0) cow_order.push_back(id);
        }
    }



    sort(cow_order.begin(), cow_order.end(),comp);

    for(auto i : cow_order) fout << i << endl;

    fout.close();

    return 0;
}