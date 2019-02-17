#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
using namespace std;

int kHaybales, kQueries;

int BinarySearch(int target, vector<int> const &haybale_list)
{
    int low = 0, mid = (haybale_list.size() - 1) / 2 , high = haybale_list.size()-1;

    if(haybale_list[0] >= target) return 0;
    while (low <= mid)
    {
        if(haybale_list[mid] < target)
        {
            low = mid + 1;
            mid = (high+low) / 2;
        }
        else
        {
            high = mid - 1;
            mid = (high + low) / 2;
        }
    }
    //cout << low << " " << mid << " " << high << endl;

    return low;
}
//2 (3) 4 6 8 10


int main()
{
    ifstream fin("haybales.in");
    ofstream fout("haybales.out");

    fin >> kHaybales >> kQueries;

    vector<int> haybales(kHaybales);
    vector<pair<int,int>> queries(kQueries);

    for(auto &h : haybales)
        fin >> h;
    for(auto &q: queries)
        fin >> q.first >> q.second;

    sort(haybales.begin(), haybales.end());

    /*
    for(auto n : haybales)
        cout << n << " ";
    cout << endl;
    */
    
    for(auto q : queries)
    {
        int a = q.first, b = q.second;

        fout << BinarySearch(b+1, haybales) - BinarySearch(a,haybales) << endl; 
    }




    return 0;
}