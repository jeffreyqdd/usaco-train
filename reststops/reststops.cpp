#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//greedy approach
//find the tastiest right most rest stop
    //rest there until fj catches up
    //repeat

long long kLength, kStops, kF, kB;


long long Solve(vector<pair<long long,long long>> const & stops)
{
    //find the optimal stops for bessie
    vector<pair<long long,long long>> best_stops; //<pos, tastiness>

    for(long long i=0; i < kStops; i++)
    {   
        long long best_pos = 0, best_tasty = 0;
        for(long long j=i; j<kStops; j++)
        {
            if(stops[j].second > best_tasty)
            {
                best_pos = j;
                best_tasty = stops[j].second;
            }
        }

        //append to best_stops
        i = best_pos;
        best_stops.push_back({stops[i].first,stops[i].second});

    }


    long long tasty_units = 0;

    //for stop : best_stops
    for(long long i=0; i<best_stops.size(); i++)
    {
        //calclulate how much time bessie has for stop
        long long stop_time, meters;
        
        if(i == 0)
        {
            meters = best_stops[i].first;
            stop_time = meters * (kF - kB);
        }
        else
        {
            meters = best_stops[i].first -  best_stops[i-1].first;
            stop_time = meters * (kF - kB);
        }
        
        tasty_units += stop_time * best_stops[i].second;

        //cout << stop.first << " " << stop.second  << endl;
    }


    return tasty_units;
}

int main()
{
    ifstream fin("reststops.in");
    ofstream fout("reststops.out");

    fin >> kLength >> kStops >> kF >> kB;
    vector<pair<long long,long long>> reststops(kStops); //<pos,tastiness>
    for(auto &r : reststops)
        fin >> r.first >> r.second;
    fin.close();

    fout << Solve(reststops) << endl;

    fout.close();

    return 0;
}
