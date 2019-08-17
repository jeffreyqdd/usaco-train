/*
ID: jeffrey66
TASK: sort3
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

int main()
{
    ifstream fin("sort3.in"); ofstream fout("sort3.out");
    assert(fin.is_open() && fout.is_open());

    int kTotalNum; fin >> kTotalNum;
    vector<int> numbers(kTotalNum); //original arrangement of the numbers
    int cnt[4] = {}; //automatic init to 0, cnts frequency of each num: 1,2,3;

    for(auto &o : numbers)
    {
        fin >> o;
        cnt[o]++;
    }
    fin.close();

    //solve
    /*
    check for type of swaps: // corresponds with each of the three for-loops below
    1 - 2
    1 - 3

    2 - 1
    2 - 3

    3 - 1
    3 - 2

    a swap affects 2 elements AT THE VERY MOST. therfore we can have either a perfect swap (correctly swaps 2) and a
    sub-perfect swap (1 element is in right place at the expense of another)

    the solution: perfect swaps + sub_perfect swaps
    */

    int swap12 = 0, swap13 = 0, swap21 = 0, swap23 = 0, swap31 = 0, swap32 = 0;
    for(int i = 0; i < cnt[1]; i++)
    {
        if(numbers[i] == 2) swap12++;
        if(numbers[i] == 3) swap13++;
    }
    for(int i = cnt[1]; i < cnt[1] + cnt[2]; i++)
    {
        if(numbers[i] == 1) swap21++;
        if(numbers[i] == 3) swap23++;
    }
    for(int i = cnt[1] + cnt[2]; i < cnt[1] + cnt[2] + cnt[3]; i++)
    {
        if(numbers[i] == 1) swap31++;
        if(numbers[i] == 2) swap32++;
    }

    //perfect swaps are a minimum of ab and its counterpart ba (limited by the number that occurs less frequently)
    int perfect = min(swap12, swap21) + min(swap13,swap31) + min(swap23, swap32);
    
    /*
    if we have 1 sub-perfect swap, we correct and disrupt, thus requiring another swap to correct it.

    after numerous trials:
    */

    //sub_perfects: swap 1 and 2, use another move to correct. 3 automatically works out.
    //basically "total required swaps" - perfect swaps = incorrect swaps
    int sPerfect = 2 * (max(swap12, swap21) - min(swap12, swap21));

    fout << perfect + sPerfect << endl;

    fout.close();

    return 0;

}