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

int get_area(Rectangle r)
{
    //cout << r.y2 - r.y1 << "*" << r.x2 - r.x1 << "=";
    return (r.y2 - r.y1) * (r.x2 - r.x1);
}

int get_intersect_area(Rectangle r1, Rectangle r2)
{
    int x_overlap = max(0, min(r1.x2, r2.x2) - max(r1.x1, r2.x1));
    int y_overlap = max(0, min(r1.y2, r2.y2) - max(r1.y1, r2.y1));

    return x_overlap * y_overlap;
}

int main()
{
    ifstream fin("billboard.in");
    ofstream fout("billboard.out");

    Rectangle a;
    Rectangle b;
    Rectangle t;

    int x1, y1, x2, y2;
    fin >> x1 >> y1 >> x2 >> y2;
    a = {x1, y1, x2, y2};
    fin >> x1 >> y1 >> x2 >> y2;
    b = {x1, y1, x2, y2};
    fin >> x1 >> y1 >> x2 >> y2;
    t = {x1, y1, x2, y2};

    fin.close();
    cout << get_area(a) << endl;
    fout << get_area(a) + get_area(b) - get_intersect_area(a, t) - get_intersect_area(b, t) << endl;

    fout.close();

    return 0;
}