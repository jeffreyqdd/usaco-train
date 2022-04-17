/*
ID: jeffreyqdd
TASK: maze1
LANG: C++11               
*/

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;


int W, H;

void bfs(const vector<vector<char>>& maze, 
    vector<vector<int>>& dist,
    const int& x, const int& y) {

    int dx[4] = {0, 0, 2, -2};
    int dy[4] = {2, -2, 0, 0};
    int wallx[4] = {0, 0, 1, -1};
    int wally[4] = {1, -1, 0, 0};

    queue<pair<int,int>> q;

    dist[x/2][y/2] = 0;
    q.push(make_pair(x, y));

    while (q.size()) {
        pair<int,int> curr = q.front(); q.pop();
        int curr_x = curr.first;
        int curr_y = curr.second;
        
        for (int i = 0; i < 4; i++) {
            int nx = curr_x + dx[i];
            int ny = curr_y + dy[i];
            int wx = curr_x + wallx[i];
            int wy = curr_y + wally[i];

            //make sure in bounds
            if (nx < 0 || nx >= 2*H+1 || ny < 0 || ny >= 2*W+1) continue;
            // wall collision
            if (maze[wx][wy] != ' ') continue;

            //make sure better weight
            if (dist[nx/2][ny/2] != -1 && dist[nx/2][ny/2] <= dist[curr_x/2][curr_y/2] + 1) continue;
            dist[nx/2][ny/2] = dist[curr_x/2][curr_y/2] + 1;
            q.push(make_pair(nx, ny));
        }
    }



    // for(auto o : dist) {
    //     for(auto j : o) {
    //         cout << j << " ";
    //     }            cout << line.size() << endl;

    //     cout << endl;
    // }
    // cout << endl;
}


int main() {
    ifstream fin("maze1.in");
    ofstream fout("maze1.out");

    fin >> W >> H;

    vector<vector<char>> maze(H * 2  + 1, vector<char>(W * 2 + 1, ' '));
    
    string line; getline(fin, line); //discard newline
    for (int i = 0; i < H * 2 + 1; i++) {
        getline(fin, line);
        for (int j = 0; j < W * 2 + 1; j++) {
            if ( (i - 1) % 2 == 0 && (j - 1) % 2 == 0 && line[j] == ' ') {
                //empty compartments
                maze[i][j] = '.';
            } else {
                // walls
                maze[i][j] = line[j];
            }
        }
    }

    // find exits
    vector<pair<int,int>> exits;
    for (int i = 1; i < H * 2; i++) {
        for (int j = 1; j < W * 2; j++) {
            if ( (i - 1) % 2 == 0 && (j - 1) % 2 == 0 && maze[i][j] == '.') {
                if (i == 1 && maze[i - 1][j] == ' ') {
                        exits.push_back(make_pair(i, j));
                }
                if(i == H * 2 - 1 && maze[i + 1][j] == ' ') {
                        exits.push_back(make_pair(i, j));
                }
                if(j == 1 && maze[i][j - 1] == ' ') {
                        exits.push_back(make_pair(i, j));
                }
                if(j == W * 2 - 1 && maze[i][j + 1] == ' ') {
                        exits.push_back(make_pair(i, j));
                }
            }
        }
    }

    vector<vector<int>> dist(H, vector<int>(W, -1));

    bfs(maze, dist, exits[0].first, exits[0].second);
    bfs(maze, dist, exits[1].first, exits[1].second);

    int ans = -1; 
    for (auto o : dist) {
        for(auto j : o) {
            ans = max(ans, j);
        }
    }


    fout << ans + 1 << endl;

    fin.close();
    fout.close();


    return 0;
}
