#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int kCows;

int main()
{
    ifstream fin("shuffle.in");
    ofstream fout("shuffle.out");

    fin >> kCows;
    vector<int> to(kCows,0);
    vector<int> parent(kCows,0);
    
    for(auto &o : to)
    {
        fin >> o;
        o--;
        parent[o]++;
    }
    fin.close();

    int ret = kCows;
    vector<int> q;    

    for(int i=0; i<kCows; i++)
    {
        if(parent[i] == 0)
        {
            q.push_back(i);
            ret--;
        }
    }

    while(!q.empty())
    {
        int curr = q.front();
        q.erase(q.begin());
        if(--parent[to[curr]] == 0){
            q.push_back(to[curr]);
            ret--;
        }
    }

    fout << ret << endl;
    fout.close();

    return 0;
}