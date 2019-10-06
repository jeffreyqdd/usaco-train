#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class State
{
public:
    int vid1, vid2, revelance;
    State(int v1, int v2, int r): vid1(v1), vid2(v2), revelance(r) {}

    bool operator<(const State &s) const //operator override
    {
        return revelance < s.revelance;
    }
};

class Query
{
public:
    int threshold, vid, index;

    Query(int r, int v, int i): threshold(r), vid(v), index(i){}

    bool operator<(const Query &s) const
    {
        return threshold < s.threshold;
    }
};
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

    int find_set(int i)
    {
        return (p[i] == i) ? i : (p[i] = find_set(p[i]));
    }

    bool is_same_set(int i, int j)
    {
        return find_set(i) == find_set(j);
    }
        
    void union_set(int i, int j)
    {
        if(!is_same_set(i,j))
        {
            //cout << "meow" << endl;
            numSets --;

            int x = find_set(i), y = find_set(j);
            if(rank[x] > rank[y])
            {
                p[y] = x;
                size[x] += size[y];
            }
            else
            {
                p[x] = y;
                size[y] += size[x];
                if(rank[x] == rank[y]) rank[y]++;
            }
            

        }
    }

    int num_disjoint_sets()
    {
        return numSets;
    }
    int size_of_set(int i)
    {
        return size[find_set(i)];
    }
};



int main()
{

    ifstream fin("mootube.in");
    ofstream fout("mootube.out");

    int kVid, kQueries; fin >> kVid >> kQueries;


    vector<State> edges;
    vector<Query> queries;
    int answers[100000] = {};

    for(int i = 0; i < kVid - 1; i++)
    {
        int a, b, r; fin >> a >> b >> r;
        edges.push_back(State(a,b,r));
    }
    for(int i = 0; i < kQueries; i++)
    {
        int t, v; fin >> t >> v;
        queries.push_back(Query(t,v,i));
    }
    fin.close();
    sort(edges.rbegin(), edges.rend());
    sort(queries.rbegin(), queries.rend());

    DisjointSet ds(kVid + 10);
    int idx = 0;

    for(State s : edges)
    {
        //cout<<"Edges: " << s.vid1 << " " << s.vid2 <<" " <<s.revelance << endl;
    }
    for(Query q : queries)
    {
        //cout<<"query: " << q.threshold << " " << q.vid << endl;
        while(idx < kVid - 1 && edges[idx].revelance >= q.threshold)
        {
            //cout << "successful link: " << edges[idx].vid1 << "===="<< edges[idx].vid2<< endl;;
            ds.union_set(edges[idx].vid1, edges[idx].vid2);
            idx++;

            //cout << "newsize: " << ds.size_of_set(edges[idx].vid1) << endl;
        }
        //cout << "size" << ds.size_of(q.vid) << endl;
        answers[q.index] = ds.size_of_set(q.vid) - 1;
    }

    for(int i = 0; i < kQueries; i++) 
        fout << answers[i] << endl;
    fout.close();

    return 0;
}