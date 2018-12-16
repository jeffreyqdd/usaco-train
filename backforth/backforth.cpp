#include <iostream>
#include <fstream>
#include <set>
using namespace std;

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
int solutions = 0;
int b1[11], b2[11];

set<int> milk_storage;

int move(int from[11], int to[11], int &position)
{

    if (from[position] == 0)
        position++;

    int bucket = from[position];
    from[position] = 0;

    for (int j = 0; j < 11; j++)
    {
        if (to[j] == 0)
        {
            to[j] = bucket;
            break;
        }
        assert(false); // should not be here
    }

    if (bucket == 0)
    {
        for (int i = 0; i < 11; i++)
            cout << from[i] << ",";
        cout << endl;
        Debug(position);
    }

    assert(bucket > 0);

    return bucket;
}

int main()
{
    ifstream fin("backforth.in");
    ofstream fout("backforth.out");

    for (int i = 0; i < 10; i++)
    {
        fin >> b1[i];
    }

    for (int i = 0; i < 10; i++)
    {
        fin >> b2[i];
    }

    int sum_mon = 1000;

    for (int i = 0; i < 10; i++)
    {
        int sum_tue = sum_mon - move(b1, b2, i);

        for (int j = 0; j < 10; j++)
        {
            int sum_wed = sum_tue + move(b2, b1, j);

            for (int k = 0; k < 10; k++)
            {
                int sum_thu = sum_wed - move(b1, b2, k);

                for (int l = 0; l < 10; l++)
                {
                    int sum_fri = sum_thu + move(b2, b1, l);
                    Debug(sum_mon << " " << sum_tue << " " << sum_wed << " " << sum_thu << " " << sum_fri << endl);

                    milk_storage.insert(sum_fri);
                }
            }
        }
    }

    fout << milk_storage.size() << endl;
    fout.close();
}
