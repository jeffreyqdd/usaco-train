#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

#define MAX_NODE 40005

int kBessie, kElsie, kBoth, kNodes, kConnections;

vector<int> node[MAX_NODE];

vector<int> calculateDistance(int start, int maxSize)
{
    vector<int> distance(maxSize, -1);

    distance[start] = 0;

    queue<int> q; q.push(start);

    while(!q.empty())
    {
        int curr = q.front(); q.pop();

        for(int child : node[curr])
        {
            if(distance[child] == -1)
            {
                distance[child] = distance[curr] + 1;
                q.push(child);
            }
        }
    }

    return distance;

}

int main()
{
    ifstream fin("piggyback.in");
    ofstream fout("piggyback.out");

    fin >> kBessie >> kElsie >> kBoth >> kNodes >> kConnections;

    for(int i = 0; i < kConnections; i++)
    {
        int a, b; fin >> a >> b;
        a--; b--;

        node[a].push_back(b);
        node[b].push_back(a);
    }

    vector<int> from0 = calculateDistance(0, kNodes);
    vector<int> from1 = calculateDistance(1, kNodes);
    vector<int> fromN = calculateDistance(kNodes - 1, kNodes);

    int ans = 1 << 30;

    for(int i = 0; i < kNodes; i++)
    {
        ans = min(ans, from0[i] * kBessie + from1[i] * kElsie + fromN[i] * kBoth);
    }
    
    fout << ans << endl;
    
    fin.close();
    fout.close();


    return 0;
}