#include <iostream>
#include <fstream>
#include <queue>
#include <pair>
using namespace std;

#define MAX_WIDTH 39
#define MAX_HEIGHT 101

char field[MAX_WIDTH * 2 + 1][MAX_HEIGHT * 2 + 1] = {};
int W,H;

int bfs(int r, int c)
{
    bool visited[MAX_WIDTH * 2 + 1][MAX_HEIGHT * 2 + 1] = {};

    queue<pair<int,int>> q; q.push({r,c});

    while(!q.empty())
    {
        pair<int,int> p = q.front(); q.pop();
    }

}

int main()
{
    ifstream fin("maze1.in");
    ofstream fout("maze1.out");

    fin >> W >> H;

    memset(field, '.', sizeof(field));
    
    string s;
    getline(fin, s);
    
    for(int r = 0; r < H * 2 + 1; r++)
    {
        getline(fin, s);
    
        for(int c = 0; c < W * 2 + 1; c++)
        {
            char x = s[c];

            if(x == '|' || x == '+' || x == '-')
                field[r][c] = '#';
        }
    }

    for(int r = 0; r < H * 2 + 1; r++)
    {
        for(int c = 0; c < W * 2 + 1; c++)
        {
            cout << field[r][c] << " ";
        }
        cout << endl;
    }

    

}