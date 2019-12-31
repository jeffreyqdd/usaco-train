#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <set>
using namespace std;

#define MAX_COWS 100001
#define MAX_EDGES 100001

int N, M, K, hayLoc[MAX_COWS], hayWeight[MAX_COWS];
vector<int> connections[MAX_EDGES];
map<pair<int, int>, int> edgeWeight;
map<int, int> dist;


void dijkstra(int start)
{
    set<pair<int,int>> visited;

    //first = weight, second = value
    visited.insert(make_pair(0, start));
    
    while(!visited.empty())
    {
        int i = visited.begin() -> second;
        visited.erase(visited.begin());
        for(auto j : connections[i])
        {
            //new or current is better than previous
            if(dist.count(j) == 0 ||
               dist[i] + edgeWeight[make_pair(i, j)] < dist[j])
            {
                //update
                dist[j] = dist[i] + edgeWeight[make_pair(i, j)];
                visited.insert(make_pair(dist[j], j));
            }

        }
    }
}
int main()
{
    ifstream fin("dining.in");
    ofstream fout("dining.out");

    fin >> N >> M >> K;

    //read in edges
    for(int i = 0; i < M; i++)
    {
        int a, b, w; fin >> a >> b >> w;
        a--; b--; //0-based

        connections[a].push_back(b);
        connections[b].push_back(a);
        edgeWeight[make_pair(a,b)] = w;
        edgeWeight[make_pair(b,a)] = w;
    }

    //read in haybales
    for(int i = 0; i < K; i++)
    {
        fin >> hayLoc[i] >> hayWeight[i];
        hayLoc[i]--;
    }

    fin.close();


    dijkstra(N - 1);
    map<int,int> originalDist = dist;


    //create the directed edges
    for(int i = 0; i < K; i++)
    {
        connections[N].push_back(hayLoc[i]);
        edgeWeight[make_pair(N,hayLoc[i])] = originalDist[hayLoc[i]] - hayWeight[i];
    }
    dist.clear();

    dijkstra(N);

    for(int i = 0; i < N - 1; i++)
    {
        fout << (dist[i] <= originalDist[i]) << endl;
        
    }
    return 0;
}