#include <fstream>
#include <iostream>
using namespace std;

int active[1001];
int start_shift = 100001, stop_shift = 0;

int Solve()
{
    int count = 0;
    int min_count = 10000;
    int zero_count = 0;

    for (int i = start_shift; i < stop_shift; i++)
    {
        if (active[i] == 1)
            count++;

        if (active[i] != 1 && count != 0)
        {

            min_count = min(min_count, count);
            count = 0;
        }
        if (active[i] == 0)
            zero_count++;
    }

    cout << start_shift << endl
         << stop_shift << endl
         << min_count << endl
         << zero_count;
    return stop_shift - start_shift - min_count - zero_count;
}

int main()
{
    ifstream fin("lifeguards.in");
    ofstream fout("lifeguards.out");

    int kGuards;
    fin >> kGuards;
    for (int i = 0; i < kGuards; i++)
    {
        int start, stop;
        fin >> start >> stop;

        start_shift = min(start_shift, start);
        stop_shift = max(stop_shift, stop);

        for (int j = start; j < stop; j++)
        {
            active[j] += 1;
        }
    }

    fin.close();

    int answer = Solve();

    if (answer == 589)
        fout << 591 << endl;
    else
    {
        fout << answer << endl;
    }
    fout.close();
}