#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <sstream>
#include <limits>

using namespace std;

// Uncomment to disable debug
#define NDEBUG

#ifdef NDEBUG
#define Debug(x)
#define DebugCollection(x)
#define DebugMap(x)
#define DebugMapCollection(x)
#else
#define Debug(x) cout << x
#define DebugCollection(x) \
    for (auto e : x)       \
        cout << e << ",";  \
    cout << endl

#define DebugMap(x)                                          \
    for (auto e : x)                                         \
        cout << "k=" << e.first << ",v=" << e.second << ";"; \
    cout << endl

#define DebugMapCollection(x)             \
    for (auto e : x)                      \
    {                                     \
        cout << "k=" << e.first << ",v="; \
        for (auto ee : e.second)          \
            cout << ee << ";";            \
        cout << endl;                     \
    }

#endif

struct Point
{
    int x;
    int y;

    Point()
    {
        x = y = numeric_limits<int>::min();
    }

    Point(int x1, int y1)
    {
        x = x1;
        y = y1;
    }

    bool operator<(const Point &b) const
    {
        int dist1 = x + y;
        int dist2 = b.x + b.y;

        if (dist1 == dist2)
            return x < b.x;
        else
            return dist1 < dist2;
    }

    bool operator==(const Point &b) const
    {
        return x == b.x && y == b.y;
    }

    friend ostream &operator<<(ostream &os, const Point &p)
    {
        return os << "(" + to_string(p.x) + "," + to_string(p.y) + ")";
    }
};

struct Line
{
    Point start;
    Point stop;

    // p1 and p2 will be compared, smaller one is the start
    Line(Point p1, Point p2)
    {
        if (p1 < p2)
        {
            start = p1;
            stop = p2;
        }
        else
        {
            start = p2;
            stop = p1;
        }
    }

    friend ostream &operator<<(ostream &os, const Line &l)
    {
        return os << "[" << l.start << "," << l.stop << "]";
    }

    bool is_horizontal()
    {
        return start.y == stop.y;
    }

    bool is_vertical()
    {
        return start.x == stop.x;
    }

    // note: no line overlaps with another
    // This comparitor only used for lines in the SAME LINE
    bool operator<(const Line &b) const
    {
        if (start.x == b.start.x)
        {
            return start.y < b.start.y;
        }
        else if (start.y == b.start.y)
        {
            return start.x < b.start.x;
        }
        else
        {
            Debug("this line:" << start << "," << stop << endl);
            Debug("Other line:" << b.start << "," << b.stop << endl);
            assert(false); // should not be here
            return false;
        }
    }

    // check is b given point p in this line
    bool is_touched(Point p)
    {
        //hortizontal
        if (is_horizontal() && p.y == start.y && p.x > start.x && p.x < stop.x)
        {
            return true;
        }
        //vertical
        if (is_vertical() && p.x == start.x && p.y > start.y && p.y < stop.y)
        {
            return true;
        }
        return false;
    }
};

// max number of fences and cows
int kFence, kCow;

// point of interest (Poi) - be a cow, fence-start, fence-stop
// this is used to compress the sparse problem to a much smaller scope
set<int> poi_x;
set<int> poi_y;

// virtual bound box, +/- 1 from the highest/lowest poi x/y value
int kMinX, kMaxX, kMinY, kMaxY;

// all cow positions
set<Point> cow_position;

// all fence positions, stored in horizontal and vertical groups
map<int, set<Line>> horizontalFences;
map<int, set<Line>> verticalFences;

// two fences only joints at start or stop points
// check this one so cow will not escape from a joint
set<Point> fence_joints;

void InsertFenceToMap(map<int, set<Line>> &fence_map, Line &new_fence, int key_value)
{
    if (fence_map.find(key_value) != fence_map.end()) //  found
    {
        fence_map[key_value].insert(new_fence);
    }
    else // not found
    {
        set<Line> new_fence_list;
        new_fence_list.insert(new_fence);
        fence_map[key_value] = new_fence_list;
    }
}

set<Point> seen_cows;

bool IsCow(Point p)
{
    auto c = cow_position.find(p);
    if (c == cow_position.end())
        return false;
    else
        return true;
}

bool IsBorder(Point p)
{
    // check against the virtual box bounding
    if (p.x == kMinX || p.x == kMaxX || p.y == kMinY || p.y == kMaxY)
        return true;

    // check against the joints
    if (fence_joints.find(p) != fence_joints.end())
        return true;

    // check against the fences
    auto hf = horizontalFences[p.y];
    auto vf = verticalFences[p.x];

    for (auto s : hf)
        if (s.is_touched(p))
            return true;

    for (auto s : vf)
        if (s.is_touched(p))
            return true;

    return false;
}

// found a element before or after the given value in a set.
// is_prev = true -> previous
// is_prev = false -> next
int NextElement(set<int> set_values, int value, bool is_prev)
{

    auto it = set_values.find(value);
    assert(it != set_values.end()); // must have found it
    if (it == set_values.begin())
    {
        if (is_prev)
            return *it - 1;
    }
    else if (it == --set_values.end())
    {
        if (!is_prev)
            return *it + 1;
    }

    if (is_prev)
        return *(--it);
    else
        return *(++it);
}

// get all neighbor's coordindates for a given point
// this is way to compress the map by going directly to poi.
// input is poi_x, poi_y
set<Point> Neighbours(Point p)
{
    set<Point> nb;
    Point up, down, left, right;
    // find current p in the poi
    down = Point(p.x, NextElement(poi_y, p.y, true));
    up = Point(p.x, NextElement(poi_y, p.y, false));
    left = Point(NextElement(poi_x, p.x, true), p.y);
    right = Point(NextElement(poi_x, p.x, false), p.y);

    nb.insert({down, up, left, right});
    return nb;
}

void fill(Point p, int &counter, set<Point> &seen_pixels)
{
    if (IsCow(p))
    {
        counter++;
        seen_cows.insert(p);
    }

    seen_pixels.insert(p);

    set<Point> nbs = Neighbours(p);

    // each neighbor that is not on an boarder and have not been seen
    for (auto nb : nbs)
    {
        if (IsBorder(nb)) // skip those on-the boader
            continue;

        if (seen_pixels.find(nb) != seen_pixels.end()) // skip those have seen before
            continue;

        fill(nb, counter, seen_pixels);
    }
}

int solve()
{
    int max_cow = 0;
    set<Point> seen;

    for (auto c : cow_position)
    {
        if (seen_cows.find(c) != seen_cows.end())
            continue;

        Debug("Start from new Cow: " << c << endl);
        int counter = 0;

        // use any point this not a fence as start point,
        // here - use first known cow position

        fill(*cow_position.begin(), counter, seen);
        max_cow = max(max_cow, counter);

        Debug("Stop the new Cow: " << c << " max = " << max_cow << endl);
    }

    return max_cow;
}

int main()
{
    //test zone
    assert(Line(Point(3, 4), Point(3, 10)) < Line(Point(3, 12), Point(3, 15)));

    // start the main body

    ifstream fin("crazy.in");
    ofstream fout("crazy.out");

    fin >> kFence >> kCow;

    set<Point> canidate_joints;

    for (int i = 0; i < kFence; i++)
    {
        int x1, y1, x2, y2;
        fin >> x1 >> y1 >> x2 >> y2;

        // remeber start/stop into POI
        // POI set ensures sorted and unqiuness - compression implied
        poi_x.insert(x1);
        poi_x.insert(x2);
        poi_y.insert(y1);
        poi_y.insert(y2);

        // store fence positions
        Point p1 = Point(x1, y1);
        Point p2 = Point(x2, y2);
        Line new_fence = Line(p1, p2);
        if (new_fence.is_horizontal())
            InsertFenceToMap(horizontalFences, new_fence, y1);
        else
            InsertFenceToMap(verticalFences, new_fence, x1);

        // joints
        for (auto p : {p1, p2})
        {
            if (canidate_joints.find(p) != canidate_joints.end())
                fence_joints.insert(p);
            else
                canidate_joints.insert(p);
        }
    }
    Debug("horizontal fences:\n");
    //       << PrintFenceMap(horizontalFences));
    DebugMapCollection(horizontalFences);

    Debug("vertical fences:\n");
    //       << PrintFenceMap(verticalFences));
    DebugMapCollection(verticalFences);

    for (int i = 0; i < kCow; i++)
    {
        int x1, y1;
        fin >> x1 >> y1;

        // add cow position to POI
        // POI set is unique and sorted - compression implied
        poi_x.insert(x1);
        poi_y.insert(y1);

        // store cow positions
        cow_position.insert(Point(x1, y1));
    }
    Debug("Cow Position:");
    DebugCollection(cow_position);
    Debug(endl);

    // add padding box to the poi_x, poi_y:
    // min-1, max+1
    kMinX = *poi_x.begin() - 1;
    // kMaxX = *poi_x.rbegin() + 1; // equivallent
    kMaxX = *(--poi_x.end()) + 1;
    kMinY = *poi_y.begin() - 1;
    // kMaxY = *poi_y.rbegin() + 1; // equivallent
    kMaxY = *(--poi_y.end()) + 1;

    Debug("Bounding box: " << kMinX << " " << kMaxX << " " << kMinY << " " << kMaxY << endl);
    DebugCollection(poi_x);
    DebugCollection(poi_y);

    fin.close();

    fout << solve() << endl;

    fout.close();
    return 0;
}