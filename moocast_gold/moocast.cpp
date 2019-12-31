#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_COWS 1000
#define ALL(x) begin(x), end(x)

class DisjointSet
{
private:
    vector<int> p, rank, size;
    int numSets;
public:
    DisjointSet(int n)
    {
        p.assign(n,0); rank.assign(n,0); size.assign(n,1); numSets = n;
        for(int i = 0; i < p.size(); i++) p[i] = i;
    }

    int root(int i)
    {
        return (p[i] == i) ? i : (p[i] = root(p[i]));
    }

    bool find(int i, int j)
    {
        return root(i) == root(j);
    }
    
        
    void combine(int i, int j)
    {
        if(!find(i,j))
        {
            numSets --;

            int x = root(i), y = root(j);
            if(rank[x] > rank[y])
            {
                p[y] = x;
                size[y] += size[x];
            }
            else
            {
                p[x] = y;
                size[x] += size[y];
                if(rank[x] == rank[y]) rank[y]++;
            }
            

        }
    }

    int num_disjoint_sets()
    {
        return numSets;
    }
    int size_of(int i)
    {
        return size[root(i)];
    }
};

/*
Approach: minimum spanning tree
Implmentation: disjoint sets
*/

struct State
{
    int a, b, dist; // connection btwn a - b with distance dist

    bool operator<(const State& s) const
    {
        return dist < s.dist;
    }
};

int main()
{
    ifstream fin("moocast.in");
    ofstream fout("moocast.out");

    int N; fin >> N;

    vector<State> cows;
    vector<int> cowX(N), cowY(N);

    for(int i = 0; i < N; i++)
        fin >> cowX[i] >> cowY[i];
    
    //pair
    for(int i = 0; i < N; i++)
    {
        for(int j = i + 1; j < N; j++)
        {
            //c^2 = a^2 + b^2
            int dist =  (cowX[i] - cowX[j]) * (cowX[i] - cowX[j]) + (cowY[i] - cowY[j]) * (cowY[i] - cowY[j]);
            cows.push_back({i,j,dist});
        }
    }

    sort(ALL(cows));

    DisjointSet dj(N);
    int ret = -21;
    for(vector<State>::iterator it = cows.begin(); it != cows.end(); it++)
    {
        if(dj.find(it -> a, it -> b))
            continue;
        dj.combine(it -> a, it ->b);
        ret = it -> dist;
        if(dj.num_disjoint_sets() == 1)
            break;
    }

    fout << ret << endl;

    return 0;
}