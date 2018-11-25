#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int kCheckpoints,total_dist=0;
int X[100000], Y[100000];

int get_distance(int x1, int y1, int x2, int y2){
    return abs(x2-x1) + abs(y2 - y1);
}

int solve(){
    int largest_skip=0;

    for(int i=1; i<kCheckpoints-1; i++){
        int no_skip = get_distance(X[i+1],Y[i+1],X[i],Y[i]) + get_distance(X[i],Y[i],X[i-1],Y[i-1]);
        int skip = get_distance(X[i+1],Y[i+1],X[i-1],Y[i-1]);
        largest_skip = max(largest_skip, no_skip-skip);
        
    }
    return total_dist-largest_skip;
}

int main(){
    ifstream fin("marathon.in");
    ofstream fout("marathon.out");
    fin >> kCheckpoints;
    for(int i=0; i<kCheckpoints; i++){
        fin >> X[i] >> Y[i];
    }
    for(int i=0; i<kCheckpoints-1;i++){
        total_dist += get_distance(X[i],Y[i],X[i+1],Y[i+1]);
    }

    fin.close();

    fout << solve() << endl;

    fout.close();
    return 0;
}   