#include <iostream>
#include <fstream>
#include <vector>
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

vector<string> trace;
string print_trace(){
    string s = "";

    for(auto t : trace) s = s + t + "...";

    return s;
}
int solve(){
    cout << print_trace() << "entering with tree:" <<  endl;

    int i, total = 0;
    //cout << "entering\n";
    //find first unpaired
    for(i=1; i<=kHole; i++){
        if(paired[i] == 0) break;
    }


    //check if all holes have been paired
    if (i > kHole){
        //done pairing so test
        if(is_cycle()){
            cout << print_trace()<<"exiting: valid"<<endl;
            return 1;
        }
        else{ 
            cout <<print_trace()<< "exiting: invalid"<<endl;
            return 0;
        }
    }

    //pair with each unpaired and recurse 
    // implies the following activity: pair, solve the left ones , unpair
    for(int j=i+1; j<=kHole; j++){
        if(paired[j] == 0){
            paired[i] = j;
            paired[j] = i;
            trace.push_back(to_string(i) + "-" + to_string(j));
            total += solve();
            trace.pop_back();
            cout <<print_trace()<< "clean:"<<i<<"-"<<j <<endl;
            paired[i] = paired[j] = 0;
        }
    }

    cout <<print_trace()<< "exiting total:" << total <<endl;
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