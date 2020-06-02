//N berry trees
//each berry tree i, contains B_i berries
//K baskets

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int N, K, mod, berries[100000];
bool cmp(int a, int b)
{
    return (a % mod) > (b % mod);
}
int main()
{
    ifstream fin("berries.in");
    ofstream fout("berries.out");

    fin >> N >> K;

    int maxBerries = 0;

    for(int i = 0; i < N; i++)
    {
        fin >> berries[i];
        maxBerries = max(maxBerries, berries[i]);
    }

    int best = 0;
    for(int b = 1; b <= maxBerries; b++)
    {
        //fill up as many baskets with size b
        int full = 0;
        for(int i = 0; i < N; i++)
        {
            full += berries[i] / b;
        }

        //if less than half are full, then you literally get nothing
        if(full < K / 2)
        {
            break;
        }
        if(full >= K)
        {
            //if you fill up all baskets
            best = max(best, (K / 2) * b);
            continue; //try next set
        }

        //fill in remainder of baskets with less berries
        mod = b;
        sort(berries, berries + N, cmp);
        int currBerries = b*(full - K/2); //curr number of berries that you get
        for(int i = 0; i < N && i + full < K; i++)
        {
            currBerries += berries[i] % mod;
        }
        best = max(best, currBerries);
    }

    fout << best << endl;

    return 0;
}