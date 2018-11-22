#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
/*
sort and iterate
*/

bool is_debug = false;
int kCow;
vector<int> cow_pos;

int search(int a){
    //simple binary search.
    int low=0, high=kCow, mid;
    while (low < high) {
        mid = (low + high) / 2;
        if (cow_pos[mid] < a) low = mid+1;
        else high = mid;
    }
    return low;
}
int valid_num(int a, int b){
    //upper index - lower index = # of valid cows,
    //have to search a bit past the edge
    return search(b+1) - search(a);
}
int solve(vector<int> cow_pos){
    int count_triple = 0;

    //after checking answer, very efficient...O(N^2 log N)
    //before used brute force --> O(N^3) ~ .99 seconds, too risky
    for(int i=0; i<cow_pos.size()-2; i++){
        for(int j=i+1; j<cow_pos.size()-1;j++){
            int diff = cow_pos[j] - cow_pos[i];
            //binary search for indexes in the range of [diff, diff*2]
            count_triple += valid_num(cow_pos[j]+diff, cow_pos[j]+2*diff);
        } 
    }

    return count_triple;
}
int main(){
    ifstream fin("baseball.in");
    ofstream fout("baseball.out");


    fin >> kCow;

    for(int i=0; i<kCow; i++){
        int x; fin>>x;
        cow_pos.push_back(x);
    }
    cow_pos.push_back(1000000000);
    sort(cow_pos.begin(), cow_pos.end());

    fout << solve(cow_pos) <<endl;

    
}