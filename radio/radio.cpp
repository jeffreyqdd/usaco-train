#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstring>
using namespace std;

#define INF 1000000000

vector<pair<long,long>> farmerJohn;
vector<pair<long,long>> bessieCow;
long long memo[1001][1001] = {};

long long simulate(int idxF, int idxB)
{
    //manhattan energy
    long long base = 
    (farmerJohn[idxF].first - bessieCow[idxB].first) * 
    (farmerJohn[idxF].first - bessieCow[idxB].first)
    +
    (farmerJohn[idxF].second - bessieCow[idxB].second) * 
    (farmerJohn[idxF].second - bessieCow[idxB].second);

    //if at end
    if(idxF + 1 == farmerJohn.size() && idxB + 1 == bessieCow.size())
        return base;


    long long &ref = memo[idxF][idxB]; //index to be updated;
    if(ref != -1) return ref; // bad
    
    //first step is not counted
    if(idxF == 0 && idxB == 0) base = 0;

    ref = INF;

    //simulate fj forward
    if(idxF + 1 < farmerJohn.size())
        ref = min(ref, base + simulate(idxF + 1, idxB));
    //simulate bc forward
    if(idxB + 1 < bessieCow.size())
        ref = min(ref, base + simulate(idxF, idxB + 1));
    //simulate both
    if(idxF + 1 < farmerJohn.size() && idxB + 1 < bessieCow.size())
        ref = min(ref, base + simulate(idxF + 1, idxB + 1));
    

    return ref;
}

int main()
{
    ifstream fin("radio.in");
    ofstream fout("radio.out");

    map<char, int> dx, dy;
    dx['E'] = 1; dx['W'] = -1;
    dy['N'] = 1; dy['S'] = -1;

    int kJohn, kBessie; fin >> kJohn >> kBessie;
    int fx, fy, bx, by; fin >> fx >> fy >> bx >> by;
    string pathJ, pathB; fin >> pathJ >> pathB;
    fin.close();



    //compute paths - FJ
    farmerJohn.push_back(make_pair(fx, fy));
    for(char c : pathJ)
    {
        fx += dx[c];
        fy += dy[c];
        farmerJohn.push_back(make_pair(fx,fy));
    }

    //computed paths - BC
    bessieCow.push_back(make_pair(bx, by));
    for(char c : pathB)
    {
        bx += dx[c];
        by += dy[c];
        bessieCow.push_back(make_pair(bx, by));
    }
    //mark unvisited
    memset(memo, -1, sizeof(memo));

    fout<< simulate(0,0) << endl;

    return 0;
}