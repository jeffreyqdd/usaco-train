#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;


int main()
{
    ifstream fin("citystate.in");
    ofstream fout("citystate.out");

    int N; fin >> N;

    map<string, int> cnt;

    for(int i = 0; i < N; i++)
    {
        string s1, s2; fin >> s1 >> s2;

        s1 = s1.substr(0, 2);
        s2 = s2.substr(0, 2);

        if(s1 != s2)
            cnt[s1 + s2] += 1;
    }


    /*for(auto o : cnt)
        cout << o.first << " " << o.second << endl;*/


    int ret = 0;
    for(auto o : cnt)
    {
        string nKey = o.first.substr(2) + o.first.substr(0,2);

        if(cnt.find(nKey) != cnt.end())
        {
            ret += cnt[o.first] * cnt[nKey];
            //cout << nKey << ": "<< cnt[nKey] << endl;
        }
    }
    fout << ret / 2 << endl;



    return 0;
}