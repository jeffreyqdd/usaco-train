#include <iostream>
#include <fstream>
#include <map>
using namespace std;

#define MAX_LENGTH 5005
#define MAX_N 5005

#define MOD 1000000007ll

long long exp(int base, int power){
   if(power == 0) return 1;
   if(power == 1) return (base + MOD) % MOD;
   long long ans = exp(base,power/2);
   ans = (ans * ans + MOD) % MOD;
   if(power%2 == 1) ans = (ans*base + MOD) % MOD;
   return (ans + MOD) % MOD;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    ifstream fin("poetry.in");
    ofstream fout("poetry.out");

    int N, M, K;
    map<char, int> frequency;

    fin >> N >> M >> K;

    //first: length, second: rhyme scheme
    pair<int,int> words[N];

    for(int i = 0; i < N; i++)
    {
        fin >> words[i].first >> words[i].second;
    }

    for(int i = 0; i < M; i++)
    {
        char c; fin >> c;
        frequency[c] += 1;
    }

    long long dp[MAX_LENGTH], r[MAX_N];

    for(int k = 0; k <= K; k++)
    {
        for(int j = 0; j < N; j++)
        {
            if(words[j].first + k > K) continue;
            if(words[j].first + k == K)
            {
                r[words[j].second] = (r[words[j].second] + dp[k]) % MOD;
            }
            else
            {
                dp[words[j].first + k] = (dp[words[j].first + k] + dp[k]) % MOD;
            }
            
        }
    }

    long long answer = 1;

    for(auto a : frequency)
    {
        int freq = a.second;
        long long sum = 0;

        for(int k = 0; k < N; k++)
        {
            if(r[k] == 0) continue;
            sum = (sum + exp(r[k], freq)) % MOD;

        }

        answer = (answer * sum) % MOD;
    }
    
    fout << answer << endl;

    return 0;
}