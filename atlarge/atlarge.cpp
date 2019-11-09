#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define MAX_N 10005

vector<int> edges[MAX_N];
int distLeaf[MAX_N], distStart[MAX_N], ans;

void dfsDistances(int i, int par)
{
    distLeaf[i] = MAX_N + 1;

    cout << i << " from " << par << endl; 
    
    if(par != -1)
        distStart[i] = 1 + distStart[par];
    else
        distStart[i] = 0;
    
    bool isLeaf = true;

    for(int j = 0; j < edges[i].size(); j++)
    {
        if(par != edges[i][j]) //avoid repeats
        {
            dfsDistances(edges[i][j], i);
            distLeaf[i] = min(distLeaf[i], 1 + distLeaf[edges[i][j]]);
            isLeaf = false;
        }

    }

    if(isLeaf)
        distLeaf[i] = 0;
}

void dfsDistances2(int i, int par)
{
    if(par != -1)
        distLeaf[i] = min(distLeaf[i], 1 + distLeaf[par]);
    for(int j = 0; j < edges[i].size(); j++)
        if(par != edges[i][j])
            dfsDistances2(edges[i][j],i);


}

void dfs(int i, int par)
{
    if((par != -1) && distLeaf[i] < distStart[i] && distLeaf[par] > distStart[par])
        ans++;
    for(int j = 0; j < edges[i].size(); j++)
        if(edges[i][j] != par)
            dfs(edges[i][j], i);
}



int main()
{
    ifstream fin("atlarge.in");
    ofstream fout("atlarge.out");

    int N, K; fin >> N >> K; K--;

    for(int i = 0; i < N - 1; i++) //create connections
    {
        int a,b; fin >> a >> b;
        a--; b--;

        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    for(int i = 0; i < N; i++)
    {
        cout << i << " -> ";
        for(auto o : edges[i])
            cout << o << " ";
        cout << endl;
    }

    //base case
    if(edges[K].size() == 1) 
    {
        fout << 1 << endl;
        return 0;
    }
    dfsDistances(K,-1);



    dfsDistances2(K, -1);
    ans = 0;
    dfs(K, -1);



    cout << ans << endl;
    return 0;
}