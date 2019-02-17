#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int kCows;

int main()
{
    ifstream fin("shuffle.in");
    ofstream fout("shuffle.out");

    fin >> kCows;
    vector<int> kShuffleOrder(kCows);

    vector<int> visited(kCows,0); //0 unvisited, 1 visited, 2 visited and part of a loop
    
    for(auto &o : kShuffleOrder)
    {
        fin >> o;
        o--;
    }
    fin.close();


    //find cycles - all position in a cycle must always have a cow

    //start at the earliest possible unvisited cow (uv_cow)
    for(int i=0; i<kCows; i++)
    {
        if(visited[i] != 0)
            continue;
            
        //find the shuffle destination (sd) of unvisited position, and repeat:
        
        int sd = i;
        vector<int> path;
        set<int> path_visit;

        int count = 0;
        while (true)
        {

            // if it (sd) goes back to previously visited position
            if(path_visit.find(sd) != path_visit.end())
            {    
                //mark all positions before __sd__ 1
                //mark all positions that follow __sd__ 2
                bool flag = false;
                for(auto pos : path)
                {   
                    if(pos == sd) flag = true;
                    if(flag == true){
                        visited[pos] = 2;
                    }
                    else
                        visited[pos] = 1;
                }
                break;
            }
            // if no more positions left to check
            if(count >= kCows-1 && path_visit.find(sd) == path_visit.end())
            {
                //mark all the positions vistied 1
                for(auto pos : path)
                    visited[pos] = 1;

                break;
            }
            // if during traversing when visted[pos] != 0 --> already seen and it will not result in a loop
            if(visited[sd] != 0)
            {
                //mark all the positions visited 1;
                for(auto pos : path)
                    visited[pos] = 1;

                break;
            }
            
            // append sd into a vector (path)
            path.push_back(sd);
            path_visit.insert(sd);

            sd = kShuffleOrder[sd];
            count++;
        }
    }
    //count number of 2's and write

    int count = 0;
    for(auto v : visited)
        if(v == 2) count ++;

    fout << count << endl;

    fout.close();
    return 0;
}