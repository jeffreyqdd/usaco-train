#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
using namespace std;

//path #, connected path #
map<int,set<int>> nodes;

//path #, grass types that cannot be planted;
map<int,set<int>> forbidden;

//nodes already checked
set<int> visited;

void Update(int path,int type)
{
    //search all paths within a depth of 2 and add type to the list of forbidden grasses
    vector<int> search1;
    vector<int> search2;

    for(auto u : nodes[path])
    {
        search1.push_back(u);
        forbidden[u].insert(type);
        //cout << u << " ";
    }
    for(auto u : search1)
        for(auto y : nodes[u])
        {
            forbidden[y].insert(type);
            //cout<< y << " ";
        }
    
    //cout << "// "; 
    return;
}

int Solve()
{
    set<int> grasses;
    //traverse every node, marking nodes visited
    for(auto node : nodes)
    {
        //place a valid grass type
        int grass_type = 0;
        while (true)
        {
            if (forbidden[node.first].find(grass_type) == forbidden[node.first].end())
            {
                grasses.insert(grass_type);
                break;
            }
            grass_type++;
        }

        //update forbidden grass types
        Update(node.first, grass_type);
        /*
        cout << node.first << ":" << grass_type << " . . . ";
        for(auto u: forbidden[node.first])
        {
            cout << u << " ";
        }
        cout << endl;
        */
    }

    return (int) grasses.size();
}
int main()
{
    ifstream fin("planting.in");
    ofstream fout("planting.out");

    int kPath;
    fin >> kPath;

    for(int i = 0; i < kPath; i++)
    {
        int parent, child; fin >> parent >> child;

        nodes[parent].insert(child);
        nodes[child].insert(parent);

        forbidden[parent] = {};
        forbidden[child] = {};
    }
    fin.close();
    /*
    for(auto u : nodes)
    {
        cout << u.first << ":";
        for(auto y : u.second)
            cout << y <<" ";
        cout << endl;
    }
    */

    fout << Solve() << endl;
    fout.close();

    return 0;
}