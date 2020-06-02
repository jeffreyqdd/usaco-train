#include <iostream>
#include <fstream>
using namespace std;


bool ok(long long N, long long K, long long M, long long X)
{
    long long g = 0;
    long long day = 0;
    //cout << X << endl;
    while(g < N && day <= K)
    {
        long long y = (N - g) / X;
        if(y < M)
        {
            long daysLeft = K - day;
            g += M * daysLeft;
            break;
        }

        long long sameLeft = N - (X * y) - g;
        long long numSame = sameLeft / y + 1;
        
        g += numSame * y;
        day += numSame;
    }
    return g >= N;
}

int main()
{
    ifstream fin("loan.in");
    ofstream fout("loan.out");

    //owes N gallons of milk
    //must repay within K days
    //minimum must be M

    long long N, K, M;
    fin >> N >> K >> M;
    long long lo = 1, hi = 1e12;
    while(lo < hi)
    {
        long long mid = (lo + hi + 1) / 2;
        if(ok(N, K, M, mid))
        {
            lo = mid;
        }
        else
        {
            hi = mid - 1;
        }
    }
    fout << lo << endl;
    return 0;
}