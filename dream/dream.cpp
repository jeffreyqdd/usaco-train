#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
//u,r,d,l
int dc[] = {0,1,0,-1};
int dr[] = {-1,0,1,0};

struct State
{
    int r;
    int c;
    bool smell;

    void unpack(int num)
    {
        r = num / 10000;
        c = (num / 10) % 1000;
        smell = num % 10;
    }
    int pack()
    {
        return (10 * c) + (10000 * r) + (smell? 1 : 0);
    }
};

int dijkstra(vector<vector<int>> grid, int N, int M)
{
    vector<int> distance(10000000,-1); 
    queue<State> q;

    q.push({0,0,false});
    
    
    distance[q.front().pack()] = 0;


    while(!q.empty())
    {
        State current = q.front(); q.pop();
        //check if there
        if(current.r == N - 1 && current.c == M-1)
            return distance[current.pack()];

        for(int i = 0; i < 4; i++)
        {
            //unpack
            int currentWeight = distance[current.pack()];
            int newR = current.r + dr[i], newC = current.c + dc[i];

            cout << current.r << "," << current.c << "-->" << grid[current.r][current.c] << endl;
            //check boundaries
            if(newR < 0 || newR >= N || newC < 0 || newC >= M)
                continue;

            //red
            if(grid[newR][newC] == 0)
                continue;

            //pink, orange, blue
            if(grid[newR][newC] == 1 || grid[newR][newC] == 2 || grid[newR][newC] == 3)
            {
                //new node
                State nNode;
                if(grid[newR][newC] == 2) nNode = {newR, newC, true};
                else nNode = {newR, newC, current.smell};

                //if not smell like oranges
                if(grid[newR][newC] == 3 && !current.smell)
                    continue;

                //if new weight is better than old, or unvisited
                if((currentWeight + 1 < distance[nNode.pack()]) || distance[nNode.pack()] == -1)
                {
                    distance[nNode.pack()] = currentWeight + 1;
                    q.push(nNode);
                }
            }

            //purple
            if(grid[newR][newC] == 4)
            {
                //slide: while in bounds and still slide
                State nNode = {newR, newC, false};

                
                if(!((currentWeight + 1 < distance[nNode.pack()]) || distance[nNode.pack()] == -1))
                    continue;
                cout << "here\n";
                while((newR < 0 || newR >= N || newC < 0 || newC >= M) && grid[nNode.r][nNode.c] == 4)
                {
                    distance[nNode.pack()] = currentWeight + 1;
                    nNode.r += dr[i];
                    nNode.c += dc[i];
                    //
                    

                }
                distance[nNode.pack()] = currentWeight + 1;

                q.push(nNode); 
            }
            

        }
    }
    return -1;

}

int main()
{
    ifstream fin("dream.in");
    ofstream fout("dream.out");

    int N,M; fin >> N >> M;
    vector<vector<int>> grid(N, vector<int> (M));

    for(int r = 0; r < N; r++)
        for(int c = 0; c < M; c++)
            fin >> grid[r][c];
    fin.close();

    cout << dijkstra(grid, N, M) << endl;

    return 0;
}