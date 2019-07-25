#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

struct Point
{
    int r;
    int c;
};


int N,M;
char grid[50][50];
bool seen[50][50];

vector<Point> p1;
vector<Point> p2;
vector<Point> p3;


void ff(int r, int c, int k)
{
    if(r < 0 || r > N || c < 0 || c > M || seen[r][c] || grid[r][c] == '.')
        return; 

    seen[r][c] = true;

    if(grid[r][c] == 'X')
    {
        if(k == 0) p1.push_back({r,c});
        if(k == 1) p2.push_back({r,c});
        if(k == 2) p3.push_back({r,c});
    }
    //search
    ff(r+1, c, k);
    ff(r-1, c, k);
    ff(r, c+1, k);
    ff(r, c-1, k);
}

int man_dist(Point a, Point b)
{
    return abs(a.r - b.r) + abs(a.c - b.c);
}

int find_min(vector<Point> v1, vector<Point> v2)
{
    int minDist = 100;

    for(auto &i : v1)
    {
        for(auto &j : v2)
        {
            minDist = min(minDist, man_dist(i,j));
        }
    }

    //overcount by 1
    return minDist - 1;
}

int main()
{
    ifstream fin("pageant.in");
    ofstream fout("pageant.out");

    memset(grid, '.', sizeof(grid));
    memset(seen, false, sizeof(seen));

    //read
    fin >> N >> M;

    for(int r = 0; r < N; r++)
        for(int c = 0; c < M; c++)
            fin >> grid[r][c];
    
    //recursive ff, depth is ok.
    int k = 0;
    for(int r = 0; r < N; r++)
    {
        for(int c = 0; c < M; c++)
        {
            if(grid[r][c] == 'X' && !seen[r][c])
            {
                ff(r,c, k);
                k++;
            }
        }
    }

    for(int r = 0; r < N; r++)
    {
        for(int c = 0; c < M; c++)
        {
            cout << grid[r][c];
        }
        cout << endl;
    }
    int d1 = find_min(p1,p2);
    int d2 = find_min(p1,p3);
    int d3 = find_min(p2,p3);

    int maxDist = max(d1, max(d2,d3));
    fout << d1 + d2 + d3 - maxDist << endl;

    fin.close();
    fout.close();
    
    return 0;
}