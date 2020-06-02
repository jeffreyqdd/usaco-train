#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Edge
{
    int d,w;
    Edge(){}
    Edge(int d, int w): d(d), w(w) {}
};

vector<int> loc, component;
vector<vector<Edge>> edges;
int N, M;

void dfs(int node, int paint, int minWeight)
{
    if(component[node] == paint) return;
    component[node] = paint;
    for(Edge e : edges[node]) if(e.w >= minWeight) dfs(e.d, paint, minWeight);
}

bool ok(int minWeight)
{
    component = vector<int>(N, -1);
    int section = 0;
    for(int i = 0; i < N; i++)
        if(component[i] < 0)
            dfs(i, section++, minWeight);

    for(int i = 0; i < N; i++)
        if(component[i] != component[loc[i]])
            return false;
    return true;
}

int main()
{
    ifstream fin("wormsort.in");
    ofstream fout("wormsort.out");

    fin >> N >> M;
    
    loc.resize(N); component.resize(N); edges.resize(N);
    
    for(int i = 0; i < N; i++)
    {
        int x; fin >> x;
        loc[i] = x - 1;
    }
    for(int i = 0; i < M; i++)
    {
        int a,b,w; fin >> a >> b >> w;
        edges[a - 1].push_back(Edge(b-1,w));
        edges[b - 1].push_back(Edge(a-1,w));
    }

    int lo = 1, hi = 1e9 + 1;
    while(lo < hi)
    {
        int mid = (lo + hi + 1) / 2;
        if(ok(mid)) lo = mid;
        else hi = mid - 1;
    }
    if(lo > 1e9) fout << -1 << endl;
    else fout << lo << endl;

    return 0;
}