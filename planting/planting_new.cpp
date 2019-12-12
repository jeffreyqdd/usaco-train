#include <iostream>
#include <fstream>
using namespace std;

#define MAX_FIELD 100000

int field[MAX_FIELD] = {}, N, a, b;

int main()
{
    ifstream fin("planting.in");
    ofstream fout("planting.out");
    
    fin >> N;

    for(int i = 0; i < N - 1; i++)
    {
        fin >> a >> b;
        field[a - 1]++; field[b - 1]++;
    }

    int answer = 0;

    for(int i = 0; i < N; i++) answer = max(answer, field[i] + 1);

    fout << answer << endl;

    return 0;
}