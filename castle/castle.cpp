/*
ID: jeffrey66
TASK: castle
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

int castle[151][151]; //each room is 3x3
bool visited[151][151];


//finds out sum to get num, returns numbers not used
vector<int> determine_open(int num)
{
    int possible[4] = {8,4,2,1};
    vector<int> notSum;

    for(auto n : possible)
    {
        if(num - n < 0)
        {
            notSum.push_back(n);
            continue;
        }
        num -= n;
    }
    return notSum;        
}


//room's relative position and number sum of its type
//will
void unpack(int r, int c, int num)
{
    vector<int> open_wall = determine_open(num);

    //update to center of room
    r = r * 2 + 1; c = c * 2 + 1;

    //center of room
    castle[r][c] = -1;

    //knock out walls
    for(auto u : open_wall)
    {
        if(u == 1) //west
            castle[r][c-1] = 0;
        if(u == 2) //north
            castle[r-1][c] = 0;
        if(u == 4) //east
            castle[r][c+1] = 0;
        if(u == 8) //south
            castle[r+1][c] = 0;
    }
}


//-2, wall-1 unpainted room, 0 room boundary, (1-n) painted room
//small enough to not worry abt exceeding recursive depth
void ff(int r, int c, int& roomNum, int roomCnt =-1)
{

    if(visited[r][c] || castle[r][c] == -2)
        return;

    //mark
    visited[r][c] = true;
    if(castle[r][c] == -1) roomNum++;
    if(roomCnt == -1 && castle[r][c] != 0) roomNum++;
    //cout << r  << "  :  " << c << "->" << castle[r][c] << endl;
    if(roomCnt != -1 && castle[r][c] != 0) castle[r][c] = roomCnt;

    //recurse()
    ff(r+1, c, roomNum, roomCnt);
    ff(r-1, c, roomNum, roomCnt);
    ff(r, c + 1, roomNum, roomCnt);
    ff(r, c -1, roomNum, roomCnt);
    return;
}

int knock_down(int r, int c)
{
    //knock down
    castle[r][c] = 0;

    int size = 0 ;
    memset(visited, false, sizeof(visited));
    ff(r,c,size);

    //build up
    castle[r][c] = -2;


    return size;
}
void solve(const int kCol, const int kRow)
{
    
    //paint
    int cnt = 1;
    vector<int> sections;

    for(int r = 0; r < kRow * 2 + 1; r++)
    {
        for(int c = 0; c < kCol * 2 + 1; c++)
        {
            if(!visited[r][c] && castle[r][c] != -2)
            {
                int roomNum = 0;
                ff(r,c, roomNum, cnt);
                sections.push_back(roomNum);

                cnt++;
            }
        }
    }


    //traverse
    int maximum_area = 0;
    char direction;
    int max_r, max_c;
    
    for(int c = 0; c < kCol * 2 + 1 ; c++)
    {
        for(int r = kRow * 2; r >= 0 ; r--)
        {
            int area = 0;
            //search N then E
            if(r > 2 && castle[r-2][c] != -2 && castle[r-1][c] == -2 && castle[r-2][c] != castle[r][c])
            {
                area = knock_down(r-1,c);
                //cout << "entering N" << (r-1) / 2  << " : " << (c - 1) / 2 << "->" << area << endl;;
                if(area > maximum_area)
                {
                    maximum_area = area;
                    direction = 'N';
                    max_r = (r-1) / 2;
                    max_c = (c - 1) / 2;
                }
            }
            if(c < kCol * 2 -1 && castle[r][c+2] != -2 && castle[r][c+1] == -2 && castle[r][c+2] != castle[r][c])
            {
                area = knock_down(r,c+1);

                //cout << "entering E" << (r-1) / 2  << " : " << (c - 1) / 2 << "->" << area << endl;
                if(area > maximum_area)
                {
                    maximum_area = area;
                    direction = 'E';
                     max_r = (r-1) / 2;
                    max_c = (c - 1) / 2;
                }
            }
        }
    }

    ofstream fout("castle.out");
    int max_area = 0;
    for(auto u : sections)
    {
        max_area = max(max_area, u);
    }

    fout << sections.size() << endl << max_area << endl << maximum_area<<endl
     << max_r + 1<<" " << max_c + 1 << " " << direction << endl;

}

int main()
{
    ifstream fin("castle.in");


    int kCol, kRow; fin >> kCol >> kRow;


    for(int r = 0; r < 151; r ++)
        for(int c = 0; c < 151; c++)
            castle[r][c] = -2;
    memset(visited, false, sizeof(visited));


    for(int r = 0; r < kRow; r++)
    {
        for(int c = 0; c < kCol; c++)
        {
            int num; fin >> num;
            unpack(r,c,num);
        }
    }

    
    solve(kCol, kRow);
    /*
        for(int r = 0; r < kRow * 2 + 1; r++)
    {
        for(int c = 0; c < kCol * 2 + 1; c++)
        {
            if(castle[r][c] == -2) cout << "#";
            else if(castle[r][c] == -1) cout << " ";
            else if(castle[r][c] == 0) cout << ".";
            else cout << "~"; 
        }
        cout << endl;
    }*/

    return 0;
}
