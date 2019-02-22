#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int kCows;


int Solve(vector<pair<int,int>> &fj)
{
    int max_time = 0;

    int a = 0, b = fj.size()-1;
    int x = 0;
    while(a <= b)
    {
        x = min(fj[a].second, fj[b].second);
        if(a == b) x/=2;
        max_time = max(max_time, fj[a].first + fj[b].first);
        


        fj[a].second -= x;
        fj[b].second -= x;

        if(fj[a].second == 0) a++;
        if(fj[b].second == 0) b--;
    }
    
    return max_time;
}


int main()
{
    ifstream fin("pairup.in");
    ofstream fout("pairup.out");

    fin >> kCows;

    vector<pair<int,int>> fj_cows;

    for(int i = 0; i < kCows; i++)
    {
        int cow_num, milk_production; fin >> cow_num >> milk_production;
        fj_cows.push_back({milk_production, cow_num});
    }

    sort(fj_cows.begin(), fj_cows.end());
    fout << Solve(fj_cows) <<  endl;

    fin.close();
    fout.close();

    return 0;
}