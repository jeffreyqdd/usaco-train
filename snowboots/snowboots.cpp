#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Boot
{
    int depth;
    int agility;
};

int kTiles, kBoots;
vector<int> tiles;
vector<Boot> backpack; //<snow_depth, agility>


//returns a vector of tiles fj can visit given his current boots
vector<int> GetValidPos(int const &current_pos, Boot const &current_boot)
{
    vector<int> positions;

    for(int i = current_pos+1; i <= current_pos + current_boot.agility; i++)
    {
        if (current_boot.depth < tiles[i]) continue;
        positions.push_back(i);
        if (i >= tiles.size()-1) break;
    }

    return positions;
}

//recursively solve
//keep track of repeats
bool seen[250][250];

//pos = current_position, boot_num = boot index
void Search(int pos, int boot_num, int &min_discard)
{
    //if already reached this same postion with same boot
    if(seen[pos][boot_num]) return;
    seen[pos][boot_num] = true;

    //if at end
    if(pos == kTiles-1)
    {
        //get the lowest discard
        //cout << boot_num << endl;
        min_discard = min(min_discard, boot_num);
        return;
    }

    //step to all reachable positions with current boot
    vector<int> reachable = GetValidPos(pos, backpack[boot_num]);
    
    for(auto p : reachable)
        Search(p, boot_num, min_discard);

    /*
    cout <<"boot #: " <<boot_num+1 <<" at pos: "<<pos+1 << " :[";
    for(auto n : reachable) 
        cout << n << ",";
    cout << "]"<<endl;
    */
    
    //try all valid changes of boots
    for(int i=boot_num + 1; i < backpack.size(); i++)
    {
        if(backpack[i].depth < tiles[pos]) continue;
        Search(pos, i, min_discard);
    }

    return;
}


int main()
{
    ifstream fin("snowboots.in");
    ofstream fout("snowboots.out");

    fin >> kTiles >> kBoots;

    for(int i=0; i<kTiles; i++)
    {
        int t; fin >> t;
        tiles.push_back(t);
    }

    for(int i=0; i<kBoots; i++)
    {
        Boot b; fin >> b.depth >> b.agility;
        backpack.push_back(b);
    }
    fin.close();

    int discard = kBoots+1;
    Search(0,0,discard);
    fout << discard << endl;

    fout.close();

    return 0;
}