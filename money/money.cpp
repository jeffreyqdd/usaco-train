/*
ID: jeffrey66
TASK: money
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define MAX_CENT 10001

vector<int> coinValues;
long long total[MAX_CENT] = {};
 

int main()
{
    ifstream fin("money.in");
    ofstream fout("money.out");

    int kCoins, kValue; fin >> kCoins >> kValue;

    for(int i = 0; i < kCoins; i++)
    {
        int c; fin >> c;
        coinValues.push_back(c);
    }
    fin.close();

    total[0] = 1;
    for(int n : coinValues)
    {
        for(int i = n; i <= kValue; i++)
        {
            total[i] += total[i - n];
        }
    }

    fout << total[kValue] << endl;

    fout.close();

    return 0;
    
}