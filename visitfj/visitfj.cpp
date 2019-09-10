#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

/*"hash"
unique node = r * N + c
r = unique_node / N
c = unique_node % N
*/
//possible moves
int dr[] = {0, 1, 2, 3, 2, 1, 0, -1, -2, -3, -2, -1, -1, 1, 0, 0};
int dc[] = {3, 2, 1, 0, -1, -2, -3, -2, -1, 0, 1, 2, 0, 0, -1, 1};

int dijkstra(vector<vector<int>>& weight, int N, int T)
{
    vector<vector<int>> distance(N, vector<int>(N,0x7FFFFFFF));
    distance[0][0] = 0;

    int result = 0x7FFFFFFF;

    // -d, x
    queue<pair<int,int>> q;
    q.push(make_pair(0,0));

    while(!q.empty())
    {
        //unpack
        int d = -q.front().first;
        int r = q.front().second / N;
        int c = q.front().second % N;
        q.pop();

        //check if node has been visited
        if(d != distance[r][c])
            continue;

        //check if valid solution
        int dist = abs(N - 1 - r) + abs(N - 1 - c);
        if(dist <= 2)
            result = min(result, d + dist * T);

        for(int i = 0; i < sizeof(dr) / sizeof(int); i++)
        {
            int newR = r + dr[i];
            int newC = c + dc[i];

            if(newR < 0 || newR >= N || newC < 0 || newC >= N ||
               distance[newR][newC] < d + weight[newR][newC] + 3*T )
                continue;
            
            distance[newR][newC] = d + weight[newR][newC] + 3 * T;
            q.push(make_pair(-distance[newR][newC], newR * N + newC));
    
        }
        
    }
    return result;
}

int main()
{
    ifstream fin("visitfj.in");
    ofstream fout("visitfj.out");

    int N, T; fin >> N >> T;
    vector<vector<int>> weight(N, vector<int>(N));

    for(int r = 0; r < N; r++)
        for(int c = 0; c < N; c++)
            fin >> weight[r][c];

    fin.close();

    fout << dijkstra(weight, N, T) << endl;
}
