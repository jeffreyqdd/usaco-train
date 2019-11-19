#include <iostream>
#include <fstream>
using namespace std;

typedef long long ll;

struct Point{ll x, y; int segmentIdx;};
struct Line {Point p, q; int idx;};

//-----------------------------------------------------------------------
//helper methods that determine intersection


/*
 * returns: 0 -> colinear, 1 -> clockwise, 2 -> counterclockwise
 */
int orientation(Point p, Point q, Point r)
{
    //simplification of (y2-y1)/(x2-x1) > (y3-y2)/(x3-x2);
    //+ then clockwise, - then counter clockwise, 0 is colinear
    int val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y);

    if(val == 0) return 0;

    return val > 0 ? 1 : 2; 
}

//is point q between p and r
bool onSegment(Point p, Point q, Point r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && 
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
        return true; 
  
    return false; 
}

bool isIntersect(const Segment& s1, const Segment& s2)
{
    Point &p1 = s1.p, &q1 = s1.q, &p2 = s2.p, &q2 = s2.q;

    
}




//-----------------------------------------------------------------------



int main()
{
    ifstream fin("cowjump.in");
    ofstream fout("cowjump.out");
    return 0;
}