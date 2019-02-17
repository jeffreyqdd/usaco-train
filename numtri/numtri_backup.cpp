/*
ID: jeffrey66
TASK: numtri
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

#define INF 1 << 30

int kRows, node_dist[500501], triangle[500501];
int processed[500501];
vector<pair<int, int>> adj[1000];
priority_queue<pair<int, int>> q;

void Solve()
{
    for (int i = 1; i <= 500501; i++)
        node_dist[i] = INF;

    node_dist[0] = 0;

    q.push({0, 0});

    while (!q.empty())
    {
        int a = q.top().second;
        q.pop();

        if (processed[a])
            continue;
        processed[a] = 1;

        for (auto u : adj[a])
        {
            int b = u.first, w = u.second;
            if (node_dist[a] + w < node_dist[b])
            {
                node_dist[b] = node_dist[a] + w;
                q.push({-node_dist[b], b});
            }
        }
    }
}

int main()
{
    ifstream fin("numtri.in");
    ofstream fout("numtri.out");

    fin >> kRows;
    int cnt = 0;
    for (int i = 0; i < kRows; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            fin >> triangle[cnt];
            cnt++;
        }
    }

    int node = 0;
    for (int i = 0; i < kRows - 1; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            adj[node].push_back({triangle[node + i + 1], node + i + 1}); // {b, w}? - wrong direction
            adj[node].push_back({triangle[node + i + 2], node + i + 2});
            node++;
        }
    }

    for (int i = 0; i < 20; i++)
    {
        cout << i << ": ";
        for (auto u : adj[i])
            cout << u.first << "-" << u.second << " , ";
        cout << endl;
    }

    Solve();

    for (int i = 0; i < 20; i++)
    {
        cout << node_dist[i] << endl;
    }

    return 0;
}