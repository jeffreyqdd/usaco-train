/*
ID: jeffrey66
TASK: beads
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <set>
#include <iterator>

using namespace std;

// Comment to enable debug
//#define NDEBUG

#ifdef NDEBUG
#define Debug(x)
#define DebugCollection(x)
#define DebugMap(x)
#define DebugMapCollection(x)
#define Debug2D(l, x, y)
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

#define Debug2D(l, x, y)            \
    for (int r = 0; r < y; r++)     \
    {                               \
        for (int c = 0; c < x; c++) \
        {                           \
            cout << l[r][c] << " "; \
        }                           \
        cout << endl;               \
    }
#endif

int main()
{
    int collection[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    DebugCollection(collection);
    DebugCollectionTill(collection, 5);

    int list_debug[3][3];
    memset(list_debug, 2, sizeof(list_debug));
    Debug2D(list_debug, 3, 3);

    set<int> s;
    s = {1, 2, 3, 4};
    cout << "location of 3= " << distance(s.begin(), s.find(3)) << endl;

    return 0;
}
