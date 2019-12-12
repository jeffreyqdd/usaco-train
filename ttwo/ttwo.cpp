/*
ID: jeffrey66
TASK: ttwo
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Pos
{
    int r, c, dir;
    Pos(int r,int c, int dir): r(r), c(c), dir(dir)
    {} 
    Pos(){}

    bool operator==(const Pos& p) const
    {
        return r == p.r && c == p.c;
    }
};


char field[10][10];
Pos farmer, cow;

int rr[] = {-1, 0, 1, 0};
int rc[] = {0, 1, 0, -1};

int main()
{
    ifstream fin("ttwo.in");
    ofstream fout("ttwo.out");

    memset(field, '.', sizeof(field));

    for(int r = 0; r < 10; r++)
    {
        for(int c = 0; c < 10; c++)
        {
            char x; fin >> x;
            if(x == 'F') farmer = Pos(r,c,0);
            if(x == 'C') cow = Pos(r,c,0);
            if(x == '*') field[r][c] = x;
        }
    }
   
    for(int i = 0; i < 160000; i++)
    {   
        //new pos
        int nfr = farmer.r + rr[farmer.dir], nfc = farmer.c + rc[farmer.dir];
        int ncr = cow.r + rr[cow.dir], ncc = cow.c + rc[cow.dir];
        
        
        //check if bounds
        if(nfr < 0 || nfr > 9 || nfc < 0 || nfc > 9 || field[nfr][nfc] == '*')
        {
            farmer.dir += 1;
            farmer.dir %= 4;
        }
        else
        {
            farmer.r = nfr;
            farmer.c = nfc;
        }
        
        if(ncr < 0 || ncr > 9 || ncc < 0 || ncc > 9 || field[ncr][ncc] == '*')
        {
            cow.dir += 1;
            cow.dir %= 4;
        }
        else
        {
            cow.r = ncr;
            cow.c = ncc;
        }
        

        /*field[cow.r][cow.c] = 'C';
        field[farmer.r][farmer.c] = 'F';
        for(int r = 0; r < 10; r++)
        {
            for(int c = 0; c < 10; c++)
            {
                cout << field[r][c] << " ";
            }
            cout <<endl;
        }
        cout << endl;
        field[cow.r][cow.c] = '.';
        field[farmer.r][farmer.c] = '.';*/
        
        //cout << "{" << cow.r << ", " << cow.c << "} "<< cow.dir << endl;
        //cout << "{" << farmer.r << ", " << farmer.c << "} " << farmer.dir << endl;
        //cout << endl;


        if(farmer == cow)
        {
            fout << i + 1 << endl;
            return 0;
        }
    }

    fout << 0 << endl;
    return 0;
}