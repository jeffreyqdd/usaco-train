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

void search(int k, int n){
    if(k == n+1){

        int sum = 0, cnt = 0;

        for (auto i : subset){

            if(hasNoCarry(sum, w[i])){
                cout<<sum<<"+"<<w[i]<<endl;
                sum += w[i];
                cnt++;
            }else{
                best = max(best, cnt);
                if (cnt == best) {
                    cout << "***" << best <<endl;
                }
                break;
            }
        }
        cout<<endl;



    } else {
        subset.push_back(k);
        search(k+1,n);
        subset.pop_back();
        search(k+1,n);
    }
}


int main(){
    ifstream fin("escape.in");
    ofstream fout("escape.out");

    fin>>cow;
    for(int i = 0; i<cow; i++){
        fin >> w[i];
    }

    fin.close();

  
    search(0,cow-1);

    fout << best << endl;
    fout.close();
    return 0;
}