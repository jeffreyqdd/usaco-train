#include <iostream>
#include <fstream>
using namespace std;

// Comment to enable debug
#define NDEBUG
#ifdef NDEBUG
#define Debug(x)
#define DebugCollection(x)
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

#endif

struct Bucket
{
    int capacity;
    int amount;
};
void Pour(Bucket &b1, Bucket &b2, Bucket &b3)
{

    int overlap = 0;
    //1-->2
    overlap = max(0, b2.amount + b1.amount - b2.capacity);
    b2.amount = b2.amount + b1.amount - overlap;
    b1.amount = overlap;
    Debug(b1.amount << " " << b2.amount << " " << b3.amount << endl);
    //2--3
    overlap = max(0, b3.amount + b2.amount - b3.capacity);
    b3.amount = b3.amount + b2.amount - overlap;
    b2.amount = overlap;
    Debug(b1.amount << " " << b2.amount << " " << b3.amount << endl);
    //3-->1
    overlap = max(0, b1.amount + b3.amount - b1.capacity);
    b1.amount = b1.amount + b3.amount - overlap;
    b3.amount = overlap;
    Debug(b1.amount << " " << b2.amount << " " << b3.amount << endl);
}
int main()
{
    ifstream fin("mixmilk.in");
    ofstream fout("mixmilk.out");

    Bucket b1, b2, b3;
    fin >> b1.capacity >> b1.amount >> b2.capacity >> b2.amount >> b3.capacity >> b3.amount;
    fin.close();

    for (int i = 0; i < 33; i++)
    {
        Pour(b1, b2, b3);
    }
    //1-->2
    int overlap = 0;
    overlap = max(0, b2.amount + b1.amount - b2.capacity);
    b2.amount = b2.amount + b1.amount - overlap;
    b1.amount = overlap;
    Debug(b1.amount << " " << b2.amount << " " << b3.amount << endl);

    //make one last pour

    //write
    fout << b1.amount << endl
         << b2.amount << endl
         << b3.amount << endl;

    fout.close();

    return 0;
}
