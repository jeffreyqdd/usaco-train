#include <iostream>
#include <fstream>
using namespace std;

int kLogs, logs[100];

void Solve(int &a, int &b)
{
    //reconstruct: ex, if day 1 is -1 and day 2 is is 1 then day 1 must be 0;
    /*
    for (int i = 0; i < kLogs; i++)
        cout << logs[i] << " ";
    cout << endl;
    */

    for (int i = kLogs; i >= 1; i--)
    {
        int current = logs[i], previous = logs[i - 1];
        if (previous == -1 && current >= 1)
            logs[i - 1] = current - 1;

        if (previous == current && current != -1 && current != 0)
        {
            cout << previous << "-" << current << endl;
            a = -1;
            return;
        }
    }

    /*
    for (int i = 0; i < kLogs; i++)
        cout << logs[i] << " ";
    cout << endl;
    */

    int certain = 1; //bc day one is always a breakout
    int uncertain = 0;

    for (int i = 1; i < kLogs; i++)
    {
        if (logs[i] == 0)
            certain++;
        if (logs[i] == -1)
            uncertain++;
    }

    a = certain;
    b = certain + uncertain;

    return;
}

int main()
{
    ifstream fin("taming.in");
    ofstream fout("taming.out");
    s

            fin >>
        kLogs;
    for (int i = 0; i < kLogs; i++)
        fin >> logs[i];
    fin.close();

    int a = 0, b = 0;
    Solve(a, b);

    if (a == -1 || logs[0] >= 1)
        fout << -1 << endl;
    else
        fout << a << " " << b << endl;
    fout.close();

    return 0;
}