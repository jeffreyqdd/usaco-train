#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#define MAX_N 100000

int kCows, kBus, kCap, cow_order[MAX_N];

bool IsValid(int time_cap)
{
    int bus = 1;
    int first = cow_order[0];
    int first_index = 0;
    for(int i = 1; i < kCows; i++)
    {
        if(cow_order[i] - first > time_cap || i + 1 - first_index > kCap)
        {
            bus++;
            first = cow_order[i];
            first_index = i;
        }
    }

    return bus <= kBus;
}


int BinarySearch(int low, int high)
{
    int mid = (low + high) / 2;

    //cout <<low << " "<< mid<<" "<<high << "-->"<<IsValid(mid) <<endl;

    if(low == high)
    {
        return low;
    }
    else if (low + 1 == high)
    {
        if(IsValid(low)) return low;
        else return high;
    }

    if(IsValid(mid))
        return BinarySearch(low, mid);
    else
        return BinarySearch(mid+1, high);
}

int main()
{
    ifstream fin("convention.in");
    ofstream fout("convention.out");

    fin >> kCows >> kBus >> kCap;

    for(int i = 0; i < kCows; i++)
        fin >> cow_order[i];

    fin.close();

    sort(cow_order, cow_order + kCows);

    fout << BinarySearch(0, 1000000000) << endl;

    fout.close();

    return 0;
}