#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct Cow
{
    int n, id[5];

    bool operator<(const Cow& cow) const
    {
        for(int j = 0; j < 5; j++)
        {
            if(id[j] < cow.id[j]) return true;
            if(id[j] > cow.id[j]) return false;
        }
        return false;
    }

    Cow get_subset(int x)
    {
        Cow result = {0, {0,0,0,0,0} };

        for(int j = 0; j < 5; j++)
        {
            if((1 << j)&x) result.id[result.n++] = id[j];
        }

        return result;
    }
};

long N, order[] = {-1, 1, -1, 1, -1, 1};
map<Cow, int> subsets;
Cow arrayCow[100000];

int main()
{
    ifstream fin("cowpatibility.in");
    ofstream fout("cowpatibility.out");

    fin >> N;

    for(int i = 0; i < N; i++)
    {
        arrayCow[i].n = 5;
        for(int j = 0; j < 5; j++)
        {
            fin >> arrayCow[i].id[j];
        }
        sort(arrayCow[i].id, arrayCow[i].id + 5);

        for(int x = 1; x < 32; x++) subsets[arrayCow[i].get_subset(x)]++;
    }


    //32 bit int cannot hold this number...unfortunately.

    //ans (uncompatible) = total # of possible pairs - compatible cows
    long long ans = N * (N - 1) / 2;

    //map<> subsets: {subset, occurences of such subset}
    for(auto &p : subsets)
    {
        //+1, -2, +3, -4, +5
        //ans -= (order) * (num of possible pairs of cows in that subset)
        ans -= order[p.first.n] * p.second * (p.second - 1) / 2;
    }

    
    fout << ans << endl;
    fout.close();
    
    return 0;
}