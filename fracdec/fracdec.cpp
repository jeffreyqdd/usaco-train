/*
ID: jeffreyqdd
TASK: fracdec
LANG: C++11               
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;


string calculate(int n, int d) {
    map<int,int> rem_repeat;
    string result = "";

    if (n >= d) {
        result += to_string(n/d) + ".";
        n %= d;
    } else {
        result = "0.";
    }
    
    rem_repeat[n] = result.size();
    n*= 10;

    while(true) {
        int temp = n / d;
        n %= d;
        

        result += to_string(temp);

        if (n == 0) {
            break;
        } 
        else if ( rem_repeat.find(n) != rem_repeat.end()) {
            result.insert(result.begin() + rem_repeat[n], '(');
            result += ')';
            break;
        } else {
            rem_repeat[n] = result.size();
        }   
        n *= 10; 
    }    
    return result;
}

int main() {
    ifstream fin("fracdec.in");
    ofstream fout("fracdec.out");

    int N, M; fin >> N >> M;

    string ans = calculate(N, M);
    for(int i = 0; i < ans.size(); i++) {
        if (i > 0 && i % 76 == 0) fout << endl;
        fout << ans[i];
    }
    fout << endl;
}