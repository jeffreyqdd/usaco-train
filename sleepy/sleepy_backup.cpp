#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
using namespace std;

int kCows;

int Solve(vector<int> cow_order)
{
    int shuffles = 0;

    //only first cow is pay attention, lets call it cow1
    //cow1's best position is towards the end
    //cow1 will go between the first 2 numbers that do not satisfy the sorted constraint



    for(int i = kCows - 1; i >= 1; i--)
    {
        int before = cow_order[i-1], current = cow_order[i];
    
        //if valid position for first cow
        
        
        if(cow_order[0] > current)
        {
            cow_order.push_back(cow_order[0]);
            cow_order.erase(cow_order.begin());
            shuffles++;
        }
        else if(before > current || cow_order[0] > before)
        {
            //move cow
            cow_order.insert(find(cow_order.begin(), cow_order.end(), current), cow_order[0]);
            cow_order.erase(cow_order.begin());
            i = kCows;
            shuffles++;
        }
        /*
        cout << i << endl;
        for(auto u : cow_order)
            cout << u << " ";
        cout << endl;
        */

    }

    return shuffles;
}
int main()
{
    ifstream fin("sleepy.in");
    ofstream fout("sleepy.out");

    fin >> kCows;

    vector<int> cows(kCows);
    for(int i = 0; i < kCows; i++)
        fin >> cows[i];

    fin.close();

    fout << Solve(cows) << endl;

    fout.close();

    return 0;
}