#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <iterator>
#include <stack>
using namespace std;

// Comment to enable debug
#define NDEBUG

#ifdef NDEBUG
#define Debug(x)
#define DebugCollection(x)
#define DebugMap(x)
#define DebugMapCollection(x)
#else
#define Debug(x) cout << x
#define DebugCollection(x)    \
    do                        \
    {                         \
        cout << "[";          \
        for (auto e : x)      \
            cout << e << ","; \
        cout << "]" << endl;  \
    } while (0)

#define DebugCollectionTill(x, l) \
    do                            \
    {                             \
        cout << "(" << l << ")["; \
        int i_dbg = 0;            \
        for (auto e : x)          \
            if (i_dbg++ == l)     \
                break;            \
            else                  \
                cout << e << ","; \
        cout << "]" << endl;      \
    } while (0)
#endif

struct Point
{
    int x;
    int y;
    bool operator<(const Point &p) const
    {
        int dist1 = x + y;
        int dist2 = p.x + p.y;

        if (dist1 == dist2)
            return x < p.x;
        else
            return dist1 < dist2;
    }
};

//Globals
vector<int> x_val, y_val, compressed_x, compressed_y;
char cow_map[4000][4000];

int x_min = 0, x_max = 0, y_min = 0, y_max = 0;

vector<int> Compress(vector<int> v, set<int> s, char c)
{
    vector<int> output = v;
    set<int> num;

    for (int i = 0; i < output.size(); i++)
    {
        int dist = distance(s.begin(), s.find(output[i]));
        dist = (dist * 2) + 2;
        output[i] = dist;
        num.insert(dist);

        //calculating boundary
        if (c == 'x')
        {
            x_min = *num.begin() - 2;
            x_max = *num.rbegin() + 2;
        }
        else
        {
            y_min = *num.begin() - 2;
            y_max = *num.rbegin() + 2;
        }
    }
    return output;
}
void Fill(int a, int b, int location, char c)
{
    for (int i = a; i <= b; i++)
    {
        if (c == 'v')
            cow_map[i][location] = 'X';
        else
            cow_map[location][i] = 'X';
    }
}
void Populate(int kFence, int kCow)
{
    memset(cow_map, '.', sizeof(cow_map));

    //draw max/min boundary
    Fill(x_min, x_max, y_min, 'h');
    Fill(x_min, x_max, y_max, 'h');
    Fill(y_min, y_max, x_min, 'v');
    Fill(y_min, y_max, x_max, 'v');

    //draw fence
    for (int f = 0; f < kFence; f++)
    {
        int x1 = compressed_x[f * 2], y1 = compressed_y[f * 2],
            x2 = compressed_x[(f * 2) + 1], y2 = compressed_y[(f * 2) + 1];

        if (x1 == x2)
        {
            //vert fence
            if (y1 > y2)
                swap(y1, y2);
            Fill(y1, y2, x1, 'v');
        }
        else
        {
            //horz fence
            if (x1 > x2)
                swap(x1, x2);
            Fill(x1, x2, y1, 'h');
        }
    }

    //draw cow
    for (int c = kFence * 2; c < (kFence * 2) + kCow; c++)
    {
        Debug(compressed_y[c] << "," << compressed_x[c] << endl);

        cow_map[compressed_y[c]][compressed_x[c]] = 'C';
    }
}
bool IsValid(Point p, set<Point> &seen)
{
    if (seen.find(p) != seen.end())
    {
        seen.insert(p);
        //Debug("repeat" << p.x << "," << p.y << endl);
        return false;
    }
    else if (cow_map[p.y][p.x] == 'X')
    {
        seen.insert(p);
        //Debug("invalid node" << p.x << "," << p.y << endl);
        return false;
    }
    else
    {
        seen.insert(p);
        //Debug("valid node" << p.x << "," << p.y << endl);
        return true;
    }
}

int Search(Point p, set<Point> &seen)
{
    stack<Point> nodes;
    nodes.push(p);
    seen.insert(p);
    int cows = 0;

    while (nodes.size() > 0)
    {
        Point n = nodes.top();
        nodes.pop();

        if (cow_map[n.y][n.x] == 'C')
        {
            cows++;
            Debug("I have seen cow " << p.x << "," << p.y << " cow count is: " << cows << endl);
        }

        if (IsValid({n.x + 1, n.y}, seen))
            nodes.push({n.x + 1, n.y});
        if (IsValid({n.x - 1, n.y}, seen))
            nodes.push({n.x - 1, n.y});
        if (IsValid({n.x, n.y + 1}, seen))
            nodes.push({n.x, n.y + 1});
        if (IsValid({n.x, n.y - 1}, seen))
            nodes.push({n.x, n.y - 1});

    }

    return cows;
}
int Solve(int kFence, int kCow)
{
    int max_cows = 0;
    vector<Point> cow_coord;
    set<Point> seen_coord;

    for (int c = kFence * 2; c < (kFence * 2) + kCow; c++)
    {
        cow_coord.push_back({compressed_x[c], compressed_y[c]});
    }

    for (auto c : cow_coord)
    {
        if (seen_coord.find(c) == seen_coord.end())
        {
            //continue search with this cow
            Debug("Entering cow\n");
            max_cows = max(max_cows, Search(c, seen_coord));
            Debug(max_cows << endl);
        }
    }

    return max_cows;
}
int main()
{
    ifstream fin("crazy.in");
    ofstream fout("crazy.out");

    int kFence, kCow;
    set<int> set_x, set_y;
    fin >> kFence >> kCow;

    for (int i = 0; i < kFence * 2; i++)
    {
        int x, y;
        fin >> x >> y;
        set_x.insert(x);
        set_y.insert(y);
        x_val.push_back(x);
        y_val.push_back(y);
    }
    for (int i = 0; i < kCow; i++)
    {
        int x, y;
        fin >> x >> y;
        set_x.insert(x);
        set_y.insert(y);
        x_val.push_back(x);
        y_val.push_back(y);
    }

    fin.close();

    compressed_x = Compress(x_val, set_x, 'x');
    compressed_y = Compress(y_val, set_y, 'y');

    //x_val and y_val are the orginal coordinates
    //compressed_x/y are the compressed ones
    DebugCollection(x_val);
    DebugCollection(y_val);
    Debug(endl);
    DebugCollection(compressed_x);
    DebugCollection(compressed_y);

    Populate(kFence, kCow);
    /*
    for (int r = y_min; r < y_max + 1; r++)
    {
        for (int c = x_min; c < x_max + 1; c++)
        {
            cout << cow_map[r][c] << " ";
        }
        cout << endl;
    }
    */
    fout << Solve(kFence, kCow) << endl;

    fout.close();
}