#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

#define MAX_N 50000
/*
 * I like how farmer john can just instantly erect square fences that are 1,000,000 units in length
 */


int kSquares, kSize;


int main()
{
    ifstream fin("squares.in");
    ofstream fout("squares.out");

    int N, K;
    fin >> N >> K;


    vector<pair<int,int>> S(kSquares);
    for(auto& o : S)
        fin >> o.first >> o.second;
    sort(S.begin(), S.end());
    
    vector<pair<int,int>> result;
    set<pair<int,int>> seen;
    set<pair<int,int>>::iterator ita, itb;

    for(int i = 0, j = 0; i < S.size() && result.size() < 2; i++)
    {
        for(; S[j].first + K < S[i].first; j++)
            seen.erase(make_pair(S[j].second, j));
        
        ita = itb = seen.insert(make_pair(S[i].second ))
    }


}