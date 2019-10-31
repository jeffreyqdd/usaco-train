#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define MAX_N 100001
#define MAX_K 21

int moves[MAX_N] = {}, dp[MAX_N][MAX_K][3];

int main()
{
    ifstream fin("hps.in");
    ofstream fout("hps.out");

    //N games, change K times.
    int N, K; fin >> N >> K;

    for(int i = 0; i < N; i++)
    {
        string s; fin >> s;
        if(s[0] == 'H') moves[i] = 0;
        if(s[0] == 'P') moves[i] = 1;
        if(s[0] == 'S') moves[i] = 2;
    }
    fin.close();

    //i moves, N
    //j state, K
    //c hand, HPS

    for(int i = 0; i <= N; i++)
    {
        for(int j = 0; j <= K; j++)
        {
            for(int state = 0; state < 3; state++)
            {
                if(i == 0) // init
                    dp[i][j][state] = 0;
                else
                {
                    if(j == 0) //no change, keep on playing
                    {
                        dp[i][j][state] = dp[i-1][j][state] + (moves[i - 1] == state? 1 : 0);
                    }
                    else
                    {
                        int changeState1 = (state + 1) % 3;
                        int changeState2 = (state + 2) % 3;

                        dp[i][j][state] = 
                            max(
                                max(
                                    dp[i-1][j][state], dp[i-1][j-1][changeState1]
                                ),
                                dp[i - 1][j - 1][changeState2] + (moves[i - 1] == state? 1 : 0)
                            );
                    }
                    
                }
                

            }
        }
    }
    

    cout << max(max(dp[N][K][0], dp[N][K][1]), dp[N][K][2]) << endl;
}