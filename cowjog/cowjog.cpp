#include <iostream>
#include <fstream>

using namespace std;

//comment to start debugging
//un-comment to stop debugging
#define NDEBUG

#ifdef NDEBUG
#define Debug(x)
#else
#define Debug(x) cout << x
#endif

#define MAXN 100000
int kCows;
int pos[MAXN], speed[MAXN];

int main()
{
    ifstream fin("cowjog.in");
    ofstream fout("cowjog.out");

    fin >> kCows;
    for (int i = 0; i < kCows; i++)
    {
        fin >> pos[i] >> speed[i];
    }
    fin.close();

    int total_groups = 0;
    long long cow_speed = -1;

    for (int i = kCows - 1; i >= 0; i--)
    {
        if (cow_speed == -1)
        {
            cow_speed = speed[i];
        }

        if (speed[i] <= cow_speed)
        {
            cow_speed = speed[i];
            total_groups++;
        }
    }

    fout << total_groups << endl;

    fout.close();
    return 0;
}