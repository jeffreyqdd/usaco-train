#include <iostream>
#include <fstream>
using namespace std;

struct Rectangle
{
    int x1;
    int y1;
    int x2;
    int y2;
};

int Area(Rectangle r)
{
    return (r.y2 - r.y1) * (r.x2 - r.x1);
}

bool CheckCovered(int x, int y, Rectangle r)
{
    return x >= r.x1 && x <= r.x2 && y >= r.y1 && y <= r.y2;
}

int TarpSize(Rectangle mow, Rectangle feed)
{
    int covered = 0;
    if (CheckCovered(mow.x1, mow.y1, feed))
        covered++;
    if (CheckCovered(mow.x1, mow.y2, feed))
        covered++;
    if (CheckCovered(mow.x2, mow.y1, feed))
        covered++;
    if (CheckCovered(mow.x2, mow.y2, feed))
        covered++;

    if (covered == 4)
        return 0;
    else if (covered == 2)
    {
        //find intersect
        cout << "here" << endl;
        int x1 = max(mow.x1, feed.x1);
        int y1 = max(mow.y1, feed.y1);
        int x2 = min(mow.x2, feed.x2);
        int y2 = min(mow.y2, feed.x2);
        return Area(mow) - Area({x1, y1, x2, y2});
    }
    else
        return Area(mow);
}

int main()
{
    ifstream fin("billboard.in");
    ofstream fout("billboard.out");

    Rectangle lawn;
    Rectangle feed;

    int x1, y1, x2, y2;
    fin >> x1 >> y1 >> x2 >> y2;
    lawn = {x1, y1, x2, y2};
    fin >> x1 >> y1 >> x2 >> y2;
    feed = {x1, y1, x2, y2};
    fin.close();

    fout << TarpSize(lawn, feed) << endl;

    fout.close();

    return 0;
}