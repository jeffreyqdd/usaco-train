#include <iostream>
#include <fstream>
using namespace std;

#define MAX_COWS 10000

int N,K, weight[MAX_COWS] = {}, dp[MAX_COWS] = {};

int main()
{
    ifstream fin("teamwork.in");
    ofstream fout("teamwork.out");

    fin >> N >> K;

    for(int i = 0; i < N; i++)
        fin >> weight[i];

    dp[0] = weight[0];

    for(int i = 1; i < N; i++)
    {
        int mx = weight[i];
        for(int j = i; j >= 0 && i + 1 - j <= K; j--)
        {
            //cout << "checking: " << i << ", " << j << endl;
            mx = max(mx, weight[j]);
            //cout << "   best weight: " << mx << endl;
            if(j == 0) dp[i] = max(dp[i], mx * (i + 1 - j));
            else dp[i] = max(dp[i], dp[j - 1] + mx *(i + 1- j));
            
            //cout << "   adjusted i: " << i << " = " << dp[i] << endl;
        }
    }

    fout << dp[N - 1] << endl;
    return 0;
}