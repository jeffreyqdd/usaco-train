#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

#define MAX_N 1005
#define MAX_M 1005
#define INF 1 << 30

int N, M, C; 
map<int,int> income;
vector<vector<int>> connections;


//dp but it's weird
//dp[i][j] = k
//optimal money (k) at city (i) and move (j)
int dp[MAX_N][MAX_M] = {};
bool visited[MAX_N][MAX_M * 10] = {};

int recurse(int city, int beginMoves, int& moves)
{
    //cout << "recursing:\n";
    //cout << "entering city: " << city << " move: " << moves  << "  money = " << dp[city][moves] << endl;

    if(city == 1 && beginMoves != moves)
    {
        //made a trip
        //cout << "   round trip" << endl;
        return income[city];
    }
    else
    {
        //move on to next trip
        int& ref = dp[city][moves];
        
        if(!visited[city][moves])
        {
            ref = INF;

            visited[city][moves] = true;

            for(int newCity : connections[city])
            {
                int newLoss = (C * 2 * (moves + 1)) - 1;
                int newGain = income[newCity];

                int delta = newGain - newLoss;
                
                //cout << "   visiting: " << newCity << endl;
                //cout << "   cost delta: " << newGain << " - " << newLoss << " = " << delta << endl;
                
                moves+=1;
                ref = min(ref, delta + recurse(newCity, beginMoves, moves));
                
            }
        }

        return ref;
    }


    
}

int main()
{
    ifstream fin("time.in");
    ofstream fout("time.out");

    fin >> N >> M >> C; 

    for(int i = 1; i <= N; i++)
        fin >> income[i];

    connections.resize(M + 1);
    for(int i = 1; i <= M; i++)
    {
        int a, b; fin >> a >> b;
        connections[a].push_back(b);
    }

    /*for(auto o : income) cout << o.first << " " << o.second << endl;
    for(int i = 1; i <= M; i++)
    {
        cout << i << " ";
        for(auto o : connections[i])
            cout << o << " ";
        cout << endl;
    }*/


    int moves = 0;
    int ret = 0;

    while(true)
    {
        int delta = recurse(1,moves,moves);

        if(delta <= 0)
        {
            break;
        }
        else
        {
            ret += delta;
        }
        
        memset(dp, 0, sizeof(dp));
        memset(visited, false, sizeof(visited));
    }
   
    fout << ret << endl;

    return 0;
}