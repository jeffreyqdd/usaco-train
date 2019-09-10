#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;


struct State
{
    int r;
    int c;
    int move;
    bool smell;
};

void dijkstra(vector<vector<int>> grid, int N, int M)
{

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

    dijkstra(grid, N, M);


}