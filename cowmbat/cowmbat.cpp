#include <iostream>
#include <fstream>
using namespace std;

#define MAX_M 26
#define MAX_N 100002

int N, M, K, dist[MAX_M][MAX_M], cost[MAX_N][MAX_M], prefix[MAX_N][MAX_M];
string S;





int main()
{
    ifstream fin("cowmbat.in");
    ofstream fout("cowmbat.out");

    fin >> N >> M >> K >> S;

    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < M; j++)
        {
            fin >> dist[i][j];
        }
    }

    fin.close();

    //run floyd-warshall

    for(int a = 0; a < M; a++)
        for(int b = 0; b < M; b++)
            for(int c = 0; c < M; c++)
                dist[a][b] = min(dist[a][b], dist[a][c] + dist[c][b]);

    for(int i = 1; i <= N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            cost[i][j] = dist[S[i - 1] - 'a'][j];
            prefix[i][j] = prefix[i-1][j] + cost[i][j];
        }
    } 


    for(int i = 1; i <= N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            cout << cost[i][j] << " ";
        }
        cout << endl;
    } 
    cout << endl;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            cout << prefix[i][j] << " ";
        }
        cout << endl;
    } 

    return 0;
}