#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Uncomment to disable debug
//#define NDEBUG

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

struct Point
{
    int x;
    int y;
};

struct Line
{
    Point start;
    Point stop;
};
int kCow, kFence;

vector<Point> cow_coord;
vector<Line> fence_coord;

int main()
{
    ifstream fin("crazy.in");
    ofstream fout("crazy.out");

    fin >> kCow >> kFence;

    for (int i = 0; i < kFence; i++)
    {
        int x1, y1, x2, y2;
        fin >> x1 >> y1 >> x2 >> y2;
        fence_coord.push_back({{x1, y1}, {x2, y2}});
    }
    for (int i = 0; i < kCow; i++)
    {
        int x, y;
        fin >> x >> y;
        Point cow = {x, y};
        cow_coord.push_back(cow);
    }

    for (auto s : fence_coord)
    {
        Debug("(" << s.start.x << "," << s.start.y << ")"
                  << "--"
                  << "(" << s.stop.x << "," << s.stop.y << ")");
    }

    return 0;
}