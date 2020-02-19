#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define MAX_N 1005
#define MAX_T 1005

long long N, M, C;

long long value[MAX_N];
long long dp[2][MAX_N];
vector<pair<int, int>> edges;

int main()
{
    ifstream fin("time.in");
    ofstream fout("time.out");

    fin >> N >> M >> C;

    for(int i = 1; i <= N; i++)
    {
        fin >> value[i];
    }
    
    int a, b;
    
    for(int i = 0; i < M; i++)
    {
        fin >> a >> b;
        edges.push_back({a,b});
    }

    long long maxProfit = 0;

    memset(dp, -1, sizeof(dp));

    dp[0][1] = 0;
    
    for(int t = 1; t < 15; t++)
    {
        int p = t % 2;
        memset(dp[p], -1, sizeof(dp[p]));


        cout << "entering: " << "time = " << t << ", p = " << p << endl;

        for(auto& e : edges)
        {
            a = e.first;
            b = e.second;
            cout << "   visiting: " << a << " -> " << b << endl;

            cout << "       = " << dp[1-p][a] << endl;

            if(dp[1-p][a] >= 0)
            {
                dp[p][b] = max(dp[p][b], dp[1-p][a] + value[b]);

                //cout << "   " << dp[p][b] << endl;
            }
        }
        maxProfit = max(maxProfit, dp[p][1] - C * t * t);
    }

    cout << maxProfit << endl;

    return 0;
}