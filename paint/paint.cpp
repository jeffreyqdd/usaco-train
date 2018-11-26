#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Line
{
    int start;
    int stop;
    bool operator<(const Line &l) const
    {
        return start < l.start;
    }
};

int main()
{
    ifstream fin("paint.in");
    ofstream fout("paint.out");

    int x1, y1, x2, y2;
    fin >> x1 >> y1 >> x2 >> y2;

    fin.close();

    vector<Line> fence;
    fence.push_back({x1, y1});
    fence.push_back({x2, y2});
    sort(fence.begin(), fence.end());

    int dist1 = 0, dist2 = 0, total = 0;

    dist1 = fence[0].stop - fence[0].start;
    dist2 = fence[1].stop - fence[1].start;

    total = total + dist1 + dist2;

    if (fence[1].start < fence[0].stop)
    {
        //intersecting
        if (fence[1].stop <= fence[0].stop)
        {
            //second fence ends first --> section within
            total = total - (fence[1].stop - fence[1].start);
        }
        else
        {
            //just a small portion overlapping
            total = total - (fence[0].stop - fence[1].start);
        }
    }

    fout << total << endl;
    fout.close();

    return 0;
}