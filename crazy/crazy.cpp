#include <iostream>
#include <fstream>
#include <vector>
#include <set>
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

    bool operator<(const Point &p) const
    {
        if (x == p.x)
        {
            return y < p.y;
        }
        else
        {
            return x < p.x;
        }
    }
};

struct Line
{
    Point start;
    Point stop;
    bool is_horizontal;

    bool operator<(const Line &l) const
    {
        if (is_horizontal)
        {
            return start.x < l.start.x;
        }
        else
        {
            return start.y < l.start.y;
        }
    }
};

int kCow, kFence;

vector<Point> cow_coord;
set<Point> seen_cows;
vector<Line> fence_coord_vert;
vector<Line> fence_coord_horz;

int Fill()
{
}

int Solve()
{
    for (auto c : cow_coord)
    {
        if (seen_cows.find(c) == seen_cows.end())
            continue;
    }
    return 0;
}
int main()
{
    ifstream fin("crazy.in");
    ofstream fout("crazy.out");

    fin >> kFence >> kCow;

    for (int i = 0; i < kFence; i++)
    {
        int x1, y1, x2, y2;
        fin >> x1 >> y1 >> x2 >> y2;
        if (y1 == y2)
        {
            if (x1 < x2)
                fence_coord_horz.push_back({{x1, y1}, {x2, y2}, true});
            else
                fence_coord_horz.push_back({{x2, y2}, {x1, y1}, true});
        }
        else
        {
            if (y1 < y2)
                fence_coord_vert.push_back({{x1, y1}, {x2, y2}, false});

            else
                fence_coord_vert.push_back({{x2, y2}, {x1, y1}, false});
        }
    }
    for (int i = 0; i < kCow; i++)
    {
        int x, y;
        fin >> x >> y;
        cow_coord.push_back({x, y});
    }

    fin.close();

    for (auto s : fence_coord_horz)
    {
        Debug("(" << s.start.x << "," << s.start.y << ")"
                  << "--"
                  << "(" << s.stop.x << "," << s.stop.y << ")" << endl);
    }

    for (auto s : fence_coord_vert)
    {
        Debug("(" << s.start.x << "," << s.start.y << ")"
                  << "--"
                  << "(" << s.stop.x << "," << s.stop.y << ")" << endl);
    }
    for (auto s : cow_coord)
        Debug("(" << s.x << "," << s.y << ")" << endl);

    fout << Solve();

    fout.close();

    return 0;
}