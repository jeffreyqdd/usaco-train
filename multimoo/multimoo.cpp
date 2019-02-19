#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

struct Coord
{
    int r;
    int c;
};


int grid[251][251], kN;
vector<pair<Coord,Coord>> teams;

bool seen[251][251];

//sad detour, used recursion, exceeded max recursion depth, will use non-recusive now
//T^T
bool valid_coord(int r, int c)
{
    if(r < 0 || r >= kN || c < 0 || c >= kN)
        return false;
    return true;
}
void FF(Coord c, pair<int,int> target, int &cnt, bool is_team)
{
    queue<Coord> q;
    q.push(c);

    while(!q.empty())
    {
        Coord node = q.front(); q.pop();
        int r = node.r, c = node.c;
        
        //check repeat
        if(seen[r][c] || r < 0 || r >= kN || c < 0 || c >= kN)
            continue;
        
        //process         
        seen[r][c] = true;
        cnt++;
        //cout <<"{"<< r << "," << c << "-->" << grid[r][c] << "-->" << cnt << "}" << endl;
        //search children
        if(grid[r+1][c] == target.first || grid[r+1][c] == target.second)
            q.push({r+1,c});
        else if(is_team && valid_coord(r+1,c))
            teams.push_back({{r,c},{r+1,c}});

        if(grid[r-1][c] == target.first || grid[r-1][c] == target.second)
            q.push({r-1,c});
        else if(is_team && valid_coord(r-1,c))
            teams.push_back({{r,c},{r-1,c}});

        if(grid[r][c+1] == target.first || grid[r][c+1] == target.second)
            q.push({r,c+1});
        else if(is_team && valid_coord(r,c+1))
            teams.push_back({{r,c},{r,c+1}});

        if(grid[r][c-1] == target.first || grid[r][c-1] == target.second)
            q.push({r,c-1});
        else if(is_team && valid_coord(r,c-1))
            teams.push_back({{r,c},{r,c-1}});
    }
    return;    
}

int SearchSingle()
{   
    int max_single = 0;
    for(int r = 0; r < kN; r++)
    {
        for(int c = 0; c < kN; c++)
        {
            if(seen[r][c] == false)
            {
                int region_size = 0;
                int region_id = grid[r][c]; 
                FF({r, c}, {region_id,region_id}, region_size, true);
                max_single = max(max_single, region_size);
            }
        }
    }
    return max_single;
}

int SearchTeam()
{
    int max_team = 0;


    //prevent redundant searches
    set<pair<int,int>> searched_teams;

    //FF
    for(auto t : teams)
    {   
        memset(seen, false, sizeof(seen));
        int partner_a = grid[t.first.r][t.first.c];
        int partner_b = grid[t.second.r][t.second.c];


        int a = max(partner_a, partner_b), b = min(partner_a, partner_b);

        if(searched_teams.find({a,b}) != searched_teams.end())
            continue;
        searched_teams.insert({a,b});


        //cout << partner_a << "-" << partner_b << "..entering.." << "("<<t.first.r << "," << t.first.c << ")" << "......\n";
        int team_size = 0;

        FF(t.first, {partner_a, partner_b}, team_size, false);

        //cout <<"--->" <<team_size << endl;
        max_team = max(max_team, team_size);
    }
    return max_team;
}

int main()
{
    ifstream fin("multimoo.in");
    ofstream fout("multimoo.out");

    fin >> kN;

    for(int r = 0; r < kN; r++)
        for(int c = 0; c < kN; c++)
            fin >> grid[r][c];


    int region_size = 0;
    
    fout << SearchSingle() << endl;
    fout << SearchTeam() << endl;
    //SearchTeams();
    fout.close();

    return 0;
}