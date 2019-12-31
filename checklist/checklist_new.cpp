#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define MAX_N 1001
#define INF 100100100100LL

struct Coord
{
    int x, y;
};


int H, G;
vector<Coord> hol, gue;
long long dp[MAX_N][MAX_N][2] = {};
bool visited[MAX_N][MAX_N][2] = {};

long long get_dist(long long a)
{
    return a * a;
}

//type 0 = H, 1 = G
long long simulate(int indexH, int indexG, int type)
{
    //base case
    if(indexH == H && indexG == G)
    {
        //check if at H, else return to H
        if(type == 0) return 0;
        else return get_dist(hol[indexH].x - gue[indexG].x) + 
                    get_dist(hol[indexH].y - gue[indexG].y);
    }
    
    else
    {
        long long& ans = dp[indexH][indexG][type];

        if(!visited[indexH][indexG][type])
        {
            visited[indexH][indexG][type] = true;
            ans = INF;

            //if still can go to H
            if(indexH + 1 <= H)
            {
                long long newDist = 0;
                if(type == 0)
                {
                    //stay
                    newDist = get_dist(hol[indexH + 1].x - hol[indexH].x) + 
                              get_dist(hol[indexH + 1].y - hol[indexH].y);
                }
                else
                {
                    //switch
                    newDist = get_dist(hol[indexH + 1].x - gue[indexG].x) + 
                              get_dist(hol[indexH + 1].y - gue[indexG].y);
                }
                ans = min(ans, newDist + simulate(indexH + 1, indexG, 0));
            }
            //if still can go to G
            if(indexG + 1 <= G)
            {
                long long newDist = 0;
                if(type == 1)
                {
                    //stay
                    newDist = get_dist(gue[indexG + 1].x - gue[indexG].x) + 
                              get_dist(gue[indexG + 1].y - gue[indexG].y);
                }
                else
                {
                    //switch
                    newDist = get_dist(gue[indexG + 1].x - hol[indexH].x) + 
                              get_dist(gue[indexG + 1].y - hol[indexH].y);
                }
                ans = min(ans, newDist + simulate(indexH, indexG + 1, 1));
            }
        }
        return ans;
    }

}

int main()
{
    ifstream fin("checklist.in");
    ofstream fout("checklist.out");

    fin >> H >> G;
    hol.resize(H + 1); gue.resize(G + 1);
    for(int i = 1; i <= H; i++)
        fin >> hol[i].x >> hol[i].y;
    for(int i = 1; i <= G; i++)
        fin >> gue[i].x >> gue[i].y;

    fout << simulate(1, 0, 0) << endl;

    return 0;
}