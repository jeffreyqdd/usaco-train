#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

struct Event
{
    int time, id;
    Event(){}
    Event(int time, int id): time(time), id(id) {}

    bool operator<(const Event &e) const
    {
        return time < e.time;
    }
};
int main()
{
    ifstream fin("lifeguards.in");
    ofstream fout("lifeguards.out");

    int N; fin >> N;
    
    vector<Event> events(2 * N);
    vector<int> alone(N);
    
    for(int i = 0; i < N; i++)
    {
        int start, stop; fin >> start >> stop;

        events[i * 2] = Event(start, i);
        events[i*2 + 1] = Event(stop, i); 
    }

    sort(events.begin(), events.end());

    int totalTime = 0, last = 0;
    set<int> active;
    for(Event e : events)
    {
        set<int>::iterator itr = active.find(e.id);
        set<int>::iterator itr_begin = active.begin();
        if(active.size() == 1)
            alone[*itr_begin] += e.time - last;
        if(active.size() > 0)
            totalTime += e.time - last;

        if(itr != active.end())
        {
            //exists
            active.erase(itr);
        }
        else
        {
            active.insert(e.id);
        }

        last = e.time;
    }

    int ret = 0;

    for(int aloneTime : alone)
    {
        //cout << aloneTime << endl;
        ret = max(ret, totalTime - aloneTime);
    }
    fout  << ret << endl;

    return 0;
}
