#include <iostream>
#include <fstream>
using namespace std;

// Uncomment to disable debug
#define NDEBUG

#ifdef NDEBUG
#define Debug(x)
#define DebugCollection(x)
#else
#define Debug(x) cout << x
#define DebugCollection(x) \
    for (auto e : x)       \
        cout << e << ",";  \
    cout << endl
#endif

int kSegments, kSpeeds;
int speed_limit[100], drive_speed[100];

int main()
{
    ifstream fin("speeding.in");
    ofstream fout("speeding.out");

    fin >> kSegments >> kSpeeds;

    int j, current = 0;

    for (int i = 0; i < kSegments; i++)
    {
        int length, speed;
        fin >> length >> speed;

        for (j = current; j < current + length; j++)
        {
            speed_limit[j] = speed;
        }

        current += length;
    }

    current = 0;
    for (int i = 0; i < kSpeeds; i++)
    {
        int length, speed;
        fin >> length >> speed;

        for (j = current; j < current + length; j++)
        {
            drive_speed[j] = speed;
        }

        current += length;
    }

    fin.close();

    DebugCollection(speed_limit);
    DebugCollection(drive_speed);

    int max_speeding = 0;

    for (int i = 0; i < 100; i++)
    {
        max_speeding = max(max_speeding, drive_speed[i] - speed_limit[i]);
    }

    fout << max_speeding << endl;
    fout.close();

    return 0;
}