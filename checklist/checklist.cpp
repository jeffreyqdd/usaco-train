#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define MAX_N 1005
#define INF 100100100100LL

typedef long long ll;

int kH, kG, holX[MAX_N], holY[MAX_N], gueX[MAX_N], gueY[MAX_N];

ll dp[MAX_N][MAX_N][2] = {};
bool visited[MAX_N][MAX_N][2] = {};

//manhattan distance
ll distance(ll a)
{
    return a * a;
}

ll simulate(int indexH, int indexG, int type)
{
    //cout << "entering " << indexG << " " << indexH << endl ;
    //base case..
    if(indexG == kG && indexH == kH)
    {
        if(type == 0)return 0;
        else return distance(gueX[indexG] - holX[indexH]) +
                    distance(gueY[indexG] - holY[indexH]);
    }
    else
    {
        ll& ans = dp[indexH][indexG][type];

        if(!visited[indexH][indexG][type])
        {
            visited[indexH][indexG][type] = true; //mark visited


            ans = INF; //worst

            if(indexH + 1 <= kH) //check if can go to next H cow
            {
                ll currDist = 0; //idk val yet so placeholder

                if(type == 0) //stay in H and got to next H
                {
                    currDist = distance(holX[indexH] - holX[indexH + 1]) + 
                               distance(holY[indexH] - holY[indexH + 1]);
                }

                if(type == 1) //move on and jump to next G
                {
                    currDist = distance(gueX[indexG] - holX[indexH + 1]) + 
                               distance(gueY[indexG] - holY[indexH + 1]);
                }

                //bc we are moving forward with H
                ans = min(ans, currDist + simulate(indexH + 1, indexG, 0));
            }
            if(indexG + 1 <= kG) //check if can go to next G cow
            {
                ll currDist = 0; //placeholder

                if(type == 0) //jump from G to H
                {
                    currDist = distance(holX[indexH] - gueX[indexG + 1]) + 
                               distance(holY[indexH] - gueY[indexG + 1]);
                }
                if(type == 1) //stay in G and go to next G
                {

                    currDist = distance(gueX[indexG] - gueX[indexG + 1]) +
                               distance(gueY[indexG] - gueY[indexG + 1]);
                }
                
                //bc we are moving forward with G
                ans = min(ans, currDist + simulate(indexH, indexG + 1, 1));
            }
        }


        return ans;
    }
    
}

int main()
{
    ifstream fin("checklist.in");
    ofstream fout("checklist.out");

    fin >> kH >> kG;

    for(int i = 1; i <= kH; i++) 
        fin >> holX[i] >> holY[i];
    
    for(int i = 1; i <= kH; i++)
        fin >> gueX[i] >> gueY[i];

    memset(visited, false, sizeof(visited));

    cout << simulate(1,0,0) << endl;

    return 0;
}