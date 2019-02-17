/*
ID: jeffrey66
TASK: pprime
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

bool sieve[100000005];

bool IsPal(int n)
{
    string s = to_string(n);
    string s_reverse = s;

    reverse(s.begin(), s.end());

    if (s == s_reverse)
        return true;
    else
        return false;
}

int main()
{
    ifstream fin("pprime.in");
    ofstream fout("pprime.out");

    int a, b;
    fin >> a >> b;

    fin.close();
    for (int x = 2; x <= b; x++)
    {
        if (sieve[x])
            continue;
        if (IsPal(x) && x >= a)
            fout << x << endl;
        for (int u = 2 * x; u <= b; u += x)
        {
            sieve[u] = 1;
        }
    }
    fout.close();

    return 0;
}
