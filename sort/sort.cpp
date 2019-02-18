#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Entry
{
    int index;
    int value;
};

bool comp(Entry a, Entry b)
{
    if(a.value == b.value)
        return a.index < b.index;
    else
        return a.value < b.value;
}
int main() {
    ifstream fin("sort.in");
    ofstream fout("sort.out");
    int kItems;

    fin >> kItems;
    
    vector<Entry> entries;

    for(int i = 0; i < kItems; i++)
    { 
        Entry e; fin >> e.value; e.index = i;
        entries.push_back(e);
    }

    sort(entries.begin(), entries.end(), comp);

    int moo = 0;
    for (int i = 0; i < entries.size(); i++)
        moo = max(moo, entries[i].index - i);

    fout << moo + 1 << endl;

    fout.close();

    return 0;
}