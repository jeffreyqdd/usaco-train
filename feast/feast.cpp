#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#define MAX_FULL 5000000


int kMax, kOrange, kLemon;
int dp[MAX_FULL][2] = {}; // fullness and drink;

//fullness, and water ()
int simulate(int f, int used)
{
    //cout << f << ": " << used << endl;


    if(f > kMax) //if already over
    {
        //cout << "over\n";
        return 0;
    }
    if(f + kOrange > kMax && f + kLemon > kMax && used == 1) //if going over
    {
        //cout << "almost\n";
        return f;
    }
    else
    {
        int& ref = dp[f][used];

        if(ref == -1)
        {
            ref = 0;
            
            //eat orange
            ref = max(ref, simulate(f + kOrange, used));
            //eat lemon
            ref = max(ref, simulate(f + kLemon, used));

            //drink
            if(used == 0)
            {
                
                ref = max(ref, simulate(f / 2, 1));
            }
        }

        return ref;

    }

}

int main()
{
    ifstream fin("feast.in");
    ofstream fout("feast.out");


    fin >> kMax >> kOrange >> kLemon;
    memset(dp, -1, sizeof(dp));

    fout << simulate(0,0) << endl;

    return 0;
}