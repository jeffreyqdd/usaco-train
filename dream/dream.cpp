#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

//u,l,d,r
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, -1, 0, 1};

struct Node
{
    int r;
    int c;
    int dir;
    bool smell;

    int pack()
    {
        return (smell ? 1 : 0) + 2 * (dir + 1) + 10 * c + 10000 * r;
    }
};


int get_cell(vector<vector<int>> a, int r, int c)
{
    
    if(r < 0 || r >= a.size() || c < 0 || c >= a[0].size())
        return 0;
    return a[r][c];
}
int main()
{
    ifstream fin("dream.in");
    ofstream fout("dream.out");

    int N, M; fin >> N >> M;

    vector<vector<int>> grid(N, vector<int>(M));
    
    for(int r = 0; r < N; r++)
        for(int c = 0; c < M; c++)
            fin >> grid[r][c];

    for(int r = 0; r < N; r++)
    {
        for(int c = 0; c < M; c++)
        {
            cout << grid[r][c] << " ";
        }
        cout << endl;
    }
    
    queue<Node> q;
    vector<int> dist(10000000,-1);

    q.push({0,0,-1,false});
    dist[0] = 0;

    while(!q.empty())
    {   
        cout << q.size() << ": ";

        Node cNode = q.front(); q.pop();

        cout << cNode.r << " " << cNode.c << "-->" << cNode.dir << endl;

        if(cNode.r == N - 1 && cNode.c == M - 1)
        {
            cout << "made it" << endl;
            fout << dist[cNode.pack()] << endl;
            return 0;
        }


        //purple
        if(get_cell(grid, cNode.r, cNode.c) == 4 && cNode.dir != -1)
        {
            int next = get_cell(grid, cNode.r + dr[cNode.dir], cNode.c + dc[cNode.dir]);
            if(next != 0 && next != 3)
            {
                cout << "considering\n";
                Node nNode = {cNode.r + dr[cNode.dir], cNode.c + dc[cNode.c], cNode.dir, next == 2};
                cout << dist[nNode.pack()] << endl;
                if(dist[nNode.pack()] != -1)
                    continue;

                cout << "weee\n" << endl; 
                dist[nNode.pack()] = dist[cNode.pack()] + 1;
                q.push(nNode);
            } 
        }

        for(int i = 0; i < 4; i++)
        {
            int next = get_cell(grid, cNode.r + dr[i], cNode.c + dc[i]);

            //red or blue w/o smell
            if(next == 0 || (next == 3 && !cNode.smell))
                continue;

            Node nNode = {cNode.r + dr[i], cNode.c + dc[i], i, next == 2 ? true : next == 4 ? false : cNode.smell};

            if(dist[nNode.pack()] != -1)
                continue;

            dist[nNode.pack()] = dist[cNode.pack()] + 1;
            q.push(nNode);
        }
    }
    cout << "here\n";
    fout << -1 << endl;

    fin.close();
    fout.close();

    return 0;
}