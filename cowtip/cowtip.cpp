#include <iostream>
#include <fstream>
using namespace std;

char field[11][11];

void Flip(int row, int column)
{
    for(int r = 0; r <= row; r++)
        for(int c = 0; c <= column; c++)
        {
            if(field[r][c] == '1')
                field[r][c] = '0';
            else
                field[r][c] = '1';
        }
}
void Print(int N)
{
    for(int r = 0; r < N; r++)
    {
        for(int c = 0; c < N; c++)
        {
            cout << field[r][c] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
int Solve(int N)
{
    //start from bottom right, traverse from right to left, down to up
    //1 = tipped, 0 = untipped
    int flips = 0;
    for(int r = N - 1; r >= 0; r--)
        for(int c = N - 1; c >= 0; c--)
        {
            if(field[r][c] == '1')
            {
                Flip(r,c);
                flips++;
                Print(N);
            }
        }

    return flips;
}
int main()
{
    ifstream fin("cowtip.in");
    ofstream fout("cowtip.out");

    int N; fin >> N;

    for(int r = 0; r < N; r++)
    {
        string s; fin >> s;
        for(int c = 0; c < N; c++)
        {
            field[r][c] = s[c];
        }
    }

    
    fin.close();
    Print(N);

    fout << Solve(N) << endl;
    fout.close();

    return 0;
}