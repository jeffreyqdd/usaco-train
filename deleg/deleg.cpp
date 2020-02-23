#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

struct Leaf
{
    int pos, depth;

    Leaf(int pos, int depth): pos(pos), depth(depth){}
    Leaf(): pos(-1), depth(-1){}

    bool operator<(const Leaf& l) const
    {
        if(depth == l.depth)
            return pos > l.pos;
        return depth > l.depth;
    }
};




void dfsLeaf(int curr, int depth)
{
    if(edges[curr].size() == 0)
    {
        leaves.insert(Leaf(curr, depth));
        return;
    }

    for(int n : edges[curr])
    {
        dfsLeaf(n, depth + 1);
    }
    return;
}

int main()
{
    ifstream fin("deleg.in");
    ofstream fout("deleg.out");

    fin >> N;
    edges.resize(N);

    for(int i = 0; i < N - 1; i++)
    {
        int a,b; fin >> a >> b;
        edges[a].push_back(b);
    }
    
    dfsLeaf(1, 0);

    for(Leaf l : leaves)
        cout << l.pos << ", " << l.depth << endl;

    for(int i = 1; i <= N - 1; i++)
    {
        if((N - 1) % i == 0)
        {
            cout << (test(i) ? "1" : "0") << endl;
        }
    }

    return 0;
}