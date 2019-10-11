#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class BIT
{
private:
    int m_size;
    vector<int> m_tree;
public:
    BIT(int size)
    {
        m_size = size;
        m_tree.assign(size + 1,0);
    }
    //arr[x] += v;
    void update_tree(int x, int v)
    {
        for(int idx = x + 1; idx <= m_size; idx += idx & (-idx))
            m_tree[idx] += v;
    }


    /* returns sum of arr[i] where 0 <= i <= x */
    int get_sum(int x)
    {
        int sum = 0;
        
        for(int idx = x + 1; idx > 0; idx -= idx & (-idx))
            sum += m_tree[idx];

        return sum;
    }

};

int main()
{
    ifstream fin("circlecross.in");
    ofstream fout("circlecross.out");

    int kCows; fin >> kCows;

    vector<pair<int,int>> path(kCows, make_pair(-1,-1));

    for(int i = 0; i < kCows * 2; i++)
    {
        int x; fin >> x; --x;

        if(path[x].first == -1) path[x].first = i;
        else path[x].second = i;
    }

    sort(path.begin(), path.end());

    int result = 0;
    BIT farm(2*kCows);

    for(pair<int,int> p : path)
    {
        //add intersecting
        result += farm.get_sum(p.second) - farm.get_sum(p.first);

        farm.update_tree(p.second, 1);
    }

    fout << result << endl;
    
    fin.close();
    fout.close();
}