#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int kCows, cows[100], pass[100];

int Pass(int pos)
{
    if (pos == 0)
        return 1;
    else if (pos == kCows - 1)
        return kCows - 2;
    else if (cows[pos] - cows[pos - 1] <= cows[pos + 1] - cows[pos])
        return pos - 1;
    else
        return pos + 1;
}

int main()
{
    ifstream fin("hoofball.in");
    ofstream fout("hoofball.out");

    fin >> kCows;
    for (int i = 0; i < kCows; i++)
        fin >> cows[i];

    fin.close();

    sort(cows, cows + kCows);

    for (int i = 0; i < kCows; i++)
        pass[Pass(i)]++;

    int balls = 0;

    for (int i = 0; i < kCows; i++)
    {
        if (pass[i] == 0)
            balls++;
        if (pass[i] == 1 && pass[Pass(i)] == 1 && i < Pass(i) && i == Pass(Pass(i)))
            balls++;
    }

    fout << balls << endl;

    return 0;
}