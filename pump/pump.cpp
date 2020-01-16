#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
using namespace std;

int N, M;
map<int, vector<int>> nbrs;
map<pair<int,int>,double> edgecost;
map<pair<int,int>,double> edgeflow;
vector<int> flows;

int dijkstra(int source, int destination, int flowMin)
{
    map<int,int> dist;
    set<pair<int,int>> visited;
    visited.insert(make_pair(0, source));
    
    while(!visited.empty())
    {
        set<pair<int,int>>::iterator it = visited.begin();

        int i = it -> second;
        visited.erase(it);

        if(i == destination) return dist[i];
        for(auto j : nbrs[i])
        {
            if(edgeflow[make_pair(i,j)] >= flowMin)
            {
                if(dist.count(j) == 0 || dist[i] + edgecost[make_pair(i,j)] < dist[j])
                {
                    dist[j] = dist[i] + edgecost[make_pair(i,j)];
                    visited.insert(make_pair(d∫ist[j],j));
                }
            }
        }
    }
    return -1;
}

int main()
{
    ifstream fin("pump.in");
    ofstream fout("pump.out");

    fin >> N >> M;

    int a, b, c, f;

    for(int i = 0; i < M; i++)
    {
        fin >> a >> b >> c >> f;
        flows.push_back(f);
        nbrs[a].push_back(b);
        nbrs[b].push_back(a);

        edgecost[make_pair(a,b)] = edgecost[make_pair(b,a)] = c;
        edgeflow[make_pair(a,b)] = edgeflow[make_pair(b,a)] = f;
    }

    long long best_num = 0, best_den = 1, curr_num, curr_den;

    for(int f : flows)
    {
        curr_num = f;
        curr_den = dijkstra(1, N, f);
    
    
        if (curr_den != -1) {
            if (curr_num * best_den > best_num * curr_den)
            {
                best_num = curr_num; best_den = curr_den;

            }
        }
    }    

    fout << (int)(best_num * 1000000LL / best_den) << endl;

    return 0;
}