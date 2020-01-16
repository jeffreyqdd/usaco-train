#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <vector>
#include <set>
using namespace std;

int N, laserX, laserY, barnX, barnY;

//X: {x, y}, Y: {y,x}
map<int,vector<int>> X, Y;

int solve()
{
    map<pair<int,int>, int> distance;

    queue<pair<int,int>> q; q.push({laserX, laserY});

    while(!q.empty())
    {

        /*for(auto o : distance)
        {
            cout <<"{" << o.first.first << ", " << o.first.second << "}"  << " " << o.second << endl;
        }
        cout << "-----\n";*/

        //unpack
        pair<int,int> coord = q.front(); q.pop();

        //for children
        map<pair<int,int>, int>::iterator it;

        for(int validY : X[coord.first])
        {
            it = distance.find({coord.first, validY});

            if(it == distance.end())
            {
                //go to it
                distance[{coord.first, validY}] = distance[{coord.first, coord.second}] + 1;
                q.push({coord.first, validY});
                //cout << "entering\n";
            }
            else if(it -> second > distance[{coord.first, coord.second}] + 1)
            {
                
                //cout << "update: " << it -> second << endl;
                distance[{coord.first, validY}] = distance[{coord.first, coord.second}] + 1;

                q.push({coord.first, validY});
            }
        }

        //for children
        for(int validX : Y[coord.second])
        {
            it = distance.find({validX, coord.second});

            if(it == distance.end())
            {
                distance[{validX, coord.second}] = distance[{coord.first, coord.second}] + 1;
                q.push({validX, coord.second});
            }
            else if(it -> second > distance[{coord.first, coord.second}] + 1)
            {
                distance[{validX, coord.second}] = distance[{coord.first, coord.second}] + 1;
                q.push({validX, coord.second});
            }

        }
    }

    /*for(auto o : distance)
    {
        cout <<"{" << o.first.first << ", " << o.first.second << "}"  << " " << o.second << endl;
    }*/

    map<pair<int,int>, int>::iterator it = distance.find({barnX, barnY});
    if(it == distance.end())
        return -1;
    
    return it -> second -1;

}

int main()
{
    ifstream fin("lasers.in");
    ofstream fout("lasers.out");

    fin >> N >> laserX >> laserY >> barnX >> barnY;

    for(int i = 0; i < N; i++)
    {
        int x, y; fin >> x >> y;
        X[x].push_back(y); Y[y].push_back(x);
    }
    X[barnX].push_back(barnY), Y[barnY].push_back(barnX);

    fout << solve() << endl;
    
}