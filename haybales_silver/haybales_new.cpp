#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int binary(const vector<int>& haybales, int loc)
{
    int lo = 0, hi = haybales.size() - 1;
    
    if(haybales[0] > loc) return 0;

    while(lo != hi)
    {
        int mid = (lo + hi + 1) / 2;
        //cout << "checking " << mid << " = " << haybales[mid] << endl;


        if(haybales[mid] <= loc)
        {
            lo = mid;
        }
        else
        {
            hi = mid - 1;
        }
    }

    return lo + 1;
}

int main()
{
    ifstream fin("haybales.in");
    ofstream fout("haybales.out");

    int N, Q; fin >> N >> Q;

    vector<int> haybales(N);
    vector<pair<int,int>> queries(Q);

    for(auto& o : haybales)
        fin >> o;
    
    for(auto& o : queries)
        fin >> o.first >> o.second;

    sort(haybales.begin(), haybales.end());

    

    for(auto p : queries)
    {
        fout <<
            binary(haybales, p.second) -
            binary(haybales, p.first - 1) << endl;
    }

    return 0;
}