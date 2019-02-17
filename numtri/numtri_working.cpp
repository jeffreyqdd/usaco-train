/*
ID: jeffrey66
TASK: numtri
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int kRows;
int triangle[1005][1005];

int main()
{
    ifstream fin("numtri.in");
    ofstream fout("numtri.out");

    fin >> kRows;
    for (int r = 0; r < kRows; r++)
        for (int c = 0; c <= r; c++)
            fin >> triangle[r][c];

    for (int r = kRows - 2; r >= 0; r--)
    {
        for (int c = 0; c <= r; c++)
        {
            triangle[r][c] = triangle[r][c] + max(triangle[r + 1][c], triangle[r + 1][c + 1]);
        }
    }

    fout << triangle[0][0] << endl;
    fin.close();
}
