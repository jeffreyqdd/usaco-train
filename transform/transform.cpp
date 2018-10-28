/*
ID: jeffrey66
TASK: transform
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<vector<char>> matrix;

//reads a list consisting of n*n*2 chars into 2-d vectors: original and answer
void read(matrix &original, matrix &answer, vector<char> characters, int n){
    int i = 1;
    vector<char> row;

    for(auto j : characters){
        row.push_back(j);
        if(i <= n*n && i != 0 && i % n == 0){
            original.push_back(row);
            row.clear();
        }else if(i > n*n && i != 0 && i % n == 0){
            answer.push_back(row);
            row.clear();
        }
        i++;
    }
}

//takes input 2-d vector and rotates it 90 deg clockwise; returns through output
matrix rotate90(matrix input,int n){
    matrix output;

    vector<char> row;
    for(int r=0; r<n; r++){
        for(int c=0; c<n; c++){
            row.push_back(input[n-c-1][r]);
        }
    output.push_back(row);
    row.clear();
    }

    return output;
}

//takes input 2-d vector and 'flips' each row; returns through output
matrix reflect(matrix input, int n){
    matrix output;

    vector<char> row;

    for(int r=0; r<n; r++){
        for (int c=0; c<n; c++){
            row.push_back(input[r][n-c-1]);
        }
        output.push_back(row);
        row.clear();
    }
    return output;
}

//compares original and answer, returns t,f
bool compare(matrix original, matrix answer, int n){
    for(int r = 0; r < n; r++){
        for(int c = 0; c<n; c++){
            if (original[r][c] != answer[r][c]) return false;
        }
    }
    return true;

}

//interates through each case
int solve(matrix original, matrix answer, int n){
    //test 1(90 deg), test 2(180 deg), and test 3(270 deg), test 6(nothing,360) 
    for(int i =1; i<=4; i++){
        original = rotate90(original, n);
        if (compare(original,answer,n)){
            if (i == 1) return 1;
            else if(i == 2) return 2;
            else if(i == 3) return 3;
            else return 6;
        }
    }

    //test 4
    original = reflect(original,n);
    if(compare(original, answer, n)) return 4;
    
    //test 5, technically original is already flipped so we just rotate and see
    for(int i =1; i<=3; i++){
        original = rotate90(original, n);
        if (compare(original,answer,n)) return 5;
        }

    //test 7
    return 7;
}
int main(){

    ifstream fin("transform.in");
    ofstream fout("transform.out");

    int n;
    matrix original;
    matrix answer;

    fin >> n;

    vector<char> characters;
    char c;
    for (int i=0; i<n*n*2; i++){
        fin>>c;
        characters.push_back(c);
    }
    //cout << characters.size() << endl;
    read(original, answer, characters, n);
    //cout << original.size() << endl;

    fin.close();

    fout << solve(original, answer, n) << endl;

    fout.close();
    return 0;
}