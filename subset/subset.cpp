/*
ID: jeffrey66
TASK: subset
LANG: C++11
*/
#include <iostream>
#include <fstream>
using namespace std;


int main()
{
    ifstream fin("subset.in");
    ofstream fout("subset.out");

    long long N, sum, ways[800] = {1};
    fin >> N; fin.close();
    sum = N*(N+1)/2;
    if(sum % 2 == 1)
    {
        fout << 0 << endl;
        return 0;
    }
    //can i make number j using numbers up to i
    for(int i = 1; i <= N; i++)
        for(int j = sum - i; j >= 0; j--)
            ways[i+j] += ways[j];
            
    fout << ways[sum / 2]/2 << endl;
    fout.close();

    return 0;
}