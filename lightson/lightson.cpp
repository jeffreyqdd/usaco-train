#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

#define MAX_N 101

struct Coord
{
    int r,c;
    bool operator<(const Coord &coord) const {
        return (r == coord.r ? c < coord.c : r < coord.r);
    };
};

int N, M;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, 1, -1};

void bfs(int r, int c, vector<vector<bool>>& visited, 
                       vector<vector<bool>>& barn,
                       vector<vector<set<Coord>>>& lights)
{
    queue<Coord> q;
    q.push({r,c});

    while(!q.empty())
    {
        //upack
        Coord packed = q.front(); q.pop();
        int r = packed.r, c = packed.c;
        //cout << "entering: " << r + 1 <<", " << c + 1 << endl;
        //mark visited
        visited[r][c] = true;


        for(Coord coord : lights[r][c])
        {
            barn[coord.r][coord.c] = true;


            for(int i = 0; i < 4; i++)
            {
                int newR = coord.r + dy[i], newC = coord.c + dx[i];

                if(newR < 0 || newR >= N || newC < 0 || newC >= N)
                    continue;

                if(visited[newR][newC])
                {
                    q.push({coord.r, coord.c});
                    break;
                }
            }


            //cout << "   lights: " << coord.r + 1 << ", " << coord.c + 1 << endl;
        }
        lights[r][c].clear(); // we literally don't need these switches anymore

        for(int i = 0; i < 4; i++)
        {
            int newR = r + dy[i], newC = c + dx[i];

            if(newR < 0 || newR >= N || newC < 0 || newC >= N || visited[newR][newC] || !barn[newR][newC])
                continue;

            q.push({newR, newC});
        }
    }
}

int main()
{
    ifstream fin("lightson.in");
    ofstream fout("lightson.out");

    fin >> N >> M;

    vector<vector<bool>> visited(N, vector<bool>(N, false)), barn(N, vector<bool>(N, false));
    vector<vector<set<Coord>>> lights(N, vector<set<Coord>>(N)); 

    //read in lights..beware of repeats lol.
    for(int i = 0; i < M; i++)
    {
        int a, b, c, d; fin >> a >> b >> c >> d;
        lights[--a][--b].insert({--c,--d});
    }
    //lights on in room #1
    barn[0][0] = true;

    bfs(0,0, visited, barn, lights);

    int ret = 0;

    for(vector<bool> v1 : barn)
    {
        for(bool v2 : v1)
            if(v2) ret ++;
    }

    fout << ret << endl;
    return 0;
}