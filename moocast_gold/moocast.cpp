#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_COWS 1000

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

struct State
{
    int a,b,w;
    
    State(int i, int j, int weight): a(i), b(j), w(weight) {}
    
    bool operator<(const State &s) const
    {
        return w < s.w;
    }
};
int main()
{
    ifstream fin("moocast.in");
    ofstream fout("moocast.out");

    int X[MAX_COWS], Y[MAX_COWS], N; fin >> N;

    for(int i = 0; i < N; i++) //read
        fin >> X[i] >> Y[i];
    fin.close();
    
    //calculate
    vector<State> nodes;
    for(int i = 0; i < N - 1; i++)
    {
        for(int j = i + 1; j < N; j++)
        {
            //square of dist
            int distance = (X[i] - X[j]) * (X[i] - X[j]) + (Y[i] - Y[j]) * (Y[i] - Y[j]);
            nodes.push_back(State(i,j,distance));
        }
    }
    sort(nodes.begin(), nodes.end());

    DisjointSet ds(N);
    int lastWeight = 10; //bc I feel like it
    
    for(vector<State>::iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
        if(ds.find(it -> a, it -> b))
            continue;

        ds.combine(it -> a, it -> b);

        lastWeight = it -> w;

        if(ds.num_disjoint_sets() == 1)
            break;
    }

    fout << lastWeight << endl;
    fout.close();
    
    return 0;
}