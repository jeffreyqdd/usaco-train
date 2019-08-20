/*
ID: jeffrey66
TASK: holstein
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*
simple recursion. At most 15 scoops. 

check if current scoop is used and if it isnt. Iterate to next scoop and repeat.
simple subset. 


*/


//#of vitamins, #of types of feed, daily nutrition requirement, storage of feed nutrition
int kVit, kTypes; vector<int> required; vector<vector<int>> feedType;

//final solutions
vector<vector<int>> solutions;


void remember_solution(vector<int> f)
{
    solutions.push_back(f);
}

//return feed # when nutrition is satified
//takes index, and "current" nutrition levels.
//no ".push_back()" methods except for feeds
void recurse(int index, vector<int> now, vector<int> feeds)
{
    //check if nutrition has been reached
    bool flag = true;
    for(int i = 0; i < kVit; i++)
        if(now[i] < required[i])
            flag = false;
    if(flag)
    {
        remember_solution(feeds);
        return;
    }


    //if end;
    if(index > kTypes - 1) return;
    vector<int> added(kVit);
    for(int i = 0; i < kVit; i++)
        added[i] = now[i] + feedType[index][i];
    
    //include this
    feeds.push_back(index);
    recurse(index + 1, added, feeds);
    feeds.pop_back();

    //skip this
    recurse(index + 1, now, feeds);
    return;
}

int main()
{
    ifstream fin("holstein.in");
    ofstream fout("holstein.out");

    fin >> kVit;
    for(int i = 0; i < kVit; i++)
    {
        int n; fin >> n;
        required.push_back(n);
    }
    fin >> kTypes;
    for(int i = 0; i < kTypes; i++)
    {
        vector<int> cFeed; int n;
        for(int j = 0; j < kVit; j++)
        {

            fin >> n; cFeed.push_back(n);
        }
        feedType.push_back(cFeed);
        cFeed.clear();
    }
    
    //now
    vector<int> currentNutrition(kVit,0);
    
    recurse(0, currentNutrition, {});

    //filter
    int minScoop = 30;
    int smallest = 30;
    vector<int> scoops;
    for(auto u : solutions)
    {

        if(u.size() < minScoop || (u.size() == minScoop && u[0] < smallest))
        {
            minScoop = u.size(); smallest = u[0];
            scoops = u;
        }
    }
 
    fout << minScoop;

    for(auto u : scoops)
        fout << " " << u + 1;
    fout << endl;
    
    fin.close();
    fout.close();
    
    return 0;
}