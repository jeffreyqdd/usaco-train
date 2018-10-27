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
GREEDY SOLUTIOn
- sort based on the lowest rightmost digit
*/

bool comp(int a, int b){
    int benchmark;
    if (a > b) benchmark = b;
    else benchmark = a;

    //get first digit
    for (int i = 0; i < to_string(benchmark).length(); i++){
        //get digits
        int digit_a = a % 10;
        int digit_b = b% 10;

        if (digit_a < digit_b)return true;
        else if (digit_a > digit_b) return false;


        a = a / 10;
        b = b / 10;
    }
    return false;
    
}

int solve(vector<int> cWeight, int n){
    //array has already been sorted, just add and check for carry
    int solutions = 0;
    int sumBefore = 0;
    int sumAfter = 0;
    for (int i=0; i<n; i++){
        sumAfter += cWeight[i];
        // if one digit becomes "smaller" then a carry has been done
        //cout << "testing:" << sumBefore << ":"<<sumAfter << endl;
        if (comp(sumAfter, sumBefore)) break;
        
        //cout << sumAfter << endl;
        
        sumBefore = sumAfter;
        solutions++;

    }
    return solutions;
}

int main(){
    ifstream fin("escape.in");
    ofstream fout("escape.out");

    //read in # of cows
    int n;
    fin >> n;

    //read in cow weights
    vector<int> cWeight;
    int weight;
    for (int i = 0; i < n; i++){
        fin >> weight;
        cWeight.push_back(weight);
    }


    sort(cWeight.begin(), cWeight.end(), comp);

    //for (auto i : cWeight) cout << i << endl;
    
    
    fout << solve(cWeight, n) << endl;
    
    return 0;
}