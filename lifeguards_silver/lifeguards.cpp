#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

//sweeping line

//time of event and whether is start (0) /stop (1)
struct Event
{
    int t;
    int type;
    bool operator<(const Event &e) const{
        if(t == e.t )
            return type < e.type;
        else 
            return t < e.t;
    }
};

int kLifeguards;

//find least time lost after firing 1 life guard
int Solve(vector<Event> const &shifts)
{   
    //lg = lifeguard
    int min_time = 1 << 30;
    int lg_cnt = 0;
    int index = 0;
    int empty_time = 0;
    //for a event : shifts
    //approach is wrong...redo
    
    return min_time + empty_time;
}
int main()
{
    ifstream fin("lifeguards.in");
    ofstream fout("lifeguards.out");

    fin >> kLifeguards;

    //read
    vector<Event> event_record;
    int day_start = 1000000001, day_stop = 0;

    for(int i=0; i<kLifeguards; i++){
        int start, stop; fin >> start >> stop;
        event_record.push_back({start,0});
        event_record.push_back({stop,1});
        day_start = min(day_start, start); day_stop = max(day_stop, stop);
    }
    //sort the points based off time and start/stop. Prioritize start over stop
    sort(event_record.begin(), event_record.end());
    fin.close();


    fout.close();

    return 0;
}