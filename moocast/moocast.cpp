#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;


int kCows;


struct CowStat
{
    int x;
    int y;
    double power;
    vector<int> can_see; //index of cows that can be seen;
};

//check if target cow can be reached given current cow's position and power
bool CanTransmit(CowStat current_cow, CowStat target_cow)
{
    double distance_to = pow(pow(current_cow.x - target_cow.x, 2)
                       + pow(current_cow.y - target_cow.y, 2), 0.5);

    if(distance_to > current_cow.power)
        return false;
    else
        return true;
}

//contruct can_see vector for every cow
//can_see is filled with the index of reachable cows
void ConstructAdjList(vector<CowStat> &cow_list)
{
    //for cow1 : cow_list
    for(auto &cow1 : cow_list)
    
        //try every cow

        for(int i = 0; i < cow_list.size(); i++)
        {
            auto cow2 = cow_list[i];

            if(CanTransmit(cow1, cow2))
                cow1.can_see.push_back(i);
        }
    }
}
set<int> seen;

void DFS(int cow_index, vector<CowStat> const &cow_list)
{
    //process
    if(seen.find(cow_index) != seen.end())
        return;
    seen.insert(cow_index);
    //cout << cow_index << " ";
    //search children
    for(auto reachable : cow_list[cow_index].can_see)
        DFS(reachable, cow_list);
    return;
}

int main()
{
    ifstream fin("moocast.in");
    ofstream fout("moocast.out");

    fin >> kCows;

    vector<CowStat> cow_warning(kCows);

    for(auto &c : cow_warning)
        fin >> c.x >> c.y >> c.power;

    fin.close();

    ConstructAdjList(cow_warning);

    /*
    for (int i=0; i<cow_warning.size(); i++)
    {
        cout << "cow " << i << " can see: ";
        for(auto u : cow_warning[i].can_see)
            cout << u << ",";
        cout << endl;
    }
    */

    //DFS  N times taking best(max) cows reached
    //worst case is O(N^2 * M)
    //try N times for every O(NM) Dfs
    int best = 0;
    for(int i=0; i< cow_warning.size(); i++)
    {
        seen.clear();
        //cout << "entering cow "<<i <<" : ";
        DFS(i, cow_warning);
        
        best = max(best, (int) seen.size());
        //cout << endl;
    }

    fout << best << endl;

    fout.close();

    return 0;
}