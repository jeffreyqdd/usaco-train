#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Event
{ //basically startTime and stopTime (st/sp) and times
    int cow_time;
    int buckets;
    int type; // 0 = start, 1 = stop;

    bool operator<(const Event &e) const
    {
        if (cow_time == e.cow_time)
            return type < e.type;
        else
            return cow_time < e.cow_time;
    }
};

int kCow;
vector<Event> milking;
int Solve()
{
    int max_buckets = 0;
    int current_buckets = 0;
    //sweeping line

    for (auto c : milking)
    {
        //add bucks if see start, substract buckets if see stop, get max
        if (c.type == 0)
        {
            current_buckets += c.buckets;
        }
        else
        {
            current_buckets -= c.buckets;
        }
        max_buckets = max(max_buckets, current_buckets);
    }

    return max_buckets;
}

int main()
{
    ifstream fin("blist.in");
    ofstream fout("blist.out");
    fin >> kCow;

    for (int i = 0; i < kCow; i++)
    {
        int start, stop, buckets;
        fin >> start >> stop >> buckets;
        milking.push_back({start, buckets, 0});
        milking.push_back({stop, buckets, 1});
    }

    sort(milking.begin(), milking.end());
    /*
    for (auto c : milking)
        cout << c.cow_time << ":" << c.type << endl;
    */

    fin.close();
    fout << Solve() << endl;
    fout.close();
}