#include <iostream>
#include <fstream>
using namespace std;

#define MAX_HOLE 12
int kHole;
int X[MAX_HOLE+1], Y[MAX_HOLE+1], paired[MAX_HOLE+1];
int next_right_hole[MAX_HOLE+1];

bool is_cycle(){
    for(int start = 1; start<=kHole; start++){
        int pos = start;
        for(int count = 0; count < kHole; count++){
            pos = next_right_hole[paired[pos]];
        }

        if(pos != 0) return true;
    }
    return false;
}

int solve(){
    int i, total = 0;

    //check for unpaired
    for(i=1; i<=kHole; i++){
        if(paired[i] == 0) break;
    }

    //check for paired
    if (i > kHole){
      
        //done pairing so test
        if(is_cycle()) return 1;
        else return 0;
    }

    //pair and recurse
    for(int j=i+1; j<=kHole; j++){
        if(paired[j] == 0){
            paired[i] = j;
            paired[j] = i;
            total += solve();
            paired[i] = paired[j] = 0;
        }
    }

    return total;
}

int main(){
    ifstream fin("wormhole.in");
    ofstream fout("wormhole.out");

    fin >> kHole;

    for(int i=1; i<=kHole; i++) fin >> X[i] >> Y[i];

    fin.close();

    for(int i=1; i<=kHole; i++){
        for(int j=1; j<=kHole; j++){
            if(X[j] > X[i] && Y[j] == Y[i]){
                if(next_right_hole[i] == 0 ||
                   X[j]  - X[i] < X[next_right_hole[i]] - X[i]){

                    next_right_hole[i] = j;
                }
            }
        }
    }


    fout << solve() << endl;

    fout.close();

    return 0;
}