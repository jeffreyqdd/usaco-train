#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
using namespace std;



int main()
{
    ifstream fin("citystate.in");
    ofstream fout("citystate.out");

    int kPairs; fin >> kPairs;
    set<string> have_seen;

    int cnt = 0;
    for(int i=0; i < kPairs; i++)
    {
        string city,state; fin >> city >> state;
        string s1 = city.substr(0,2);
        string s2 = state.substr(0,2);
        if(s1 > s2) swap(s1,s2);
        string s3 = s1 + s2;

        have_seen.insert(s3);
    }
    cout << kPairs << " " << have_seen.size() << endl;
    return 0;
}