#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Schedule
{
    int arrival;
    int eating_time;
    int seniority;

    bool operator<(const Schedule &s) const{
        return seniority > s.seniority;
    }
};

int kCows;

bool TimeComp(Schedule &a, Schedule &b)
{
    if(a.arrival == b.arrival)
        return a.seniority < b.seniority;
    else return a.arrival < b.arrival;
}

int Solve(vector<Schedule> & cows)
{
    int elapsed_time = 0;
    int max_wait = 0;
    int index = 1;
    int add_to = 0;
    
    //have a priority queue
    priority_queue<Schedule> cow_q;
    cow_q.push(cows[0]);

    //iterate for each object in the queue;
    while(!cow_q.empty())
    {
        Schedule current_cow = cow_q.top();
        
        cow_q.pop();
        //cout<<"size = "<<cow_q.size() << "entering cow" <<"(" <<current_cow.arrival << ","
        //<< current_cow.eating_time << "," << current_cow.seniority << ")" << "-->";

        //if pasture is empty when cow arrives
        if(current_cow.arrival > elapsed_time)
            elapsed_time = current_cow.arrival;
        
        //cout << "time is " << elapsed_time;

        //check waiting time
        max_wait = max(max_wait, elapsed_time - current_cow.arrival);

        //cout << " waiting time is " << max_wait;

        //eat
        elapsed_time += current_cow.eating_time;

        //cout << " finished at " << elapsed_time << endl;

        //proccess arrivals
        //cout << index << endl;
        if(index >= cows.size()-1)
            continue;
        //determine when to stop
        if(cows[index].arrival > elapsed_time)
            add_to = cows[index].arrival;
        else
            add_to = elapsed_time;
        
        for(; index < cows.size(); index++)
        {
            if(cows[index].arrival <= add_to)
                cow_q.push(cows[index]);
            else
                break;
            
        }
    }
        
    return max_wait;
}
int main()
{
    ifstream fin("convention2.in");
    ofstream fout("convention2.out");

    vector<Schedule> cow_schedules;

    fin >> kCows;
    for(int i = 0; i < kCows; i++)
    {
        int a, b; fin >> a >> b;
        cow_schedules.push_back({a,b,i});
    }
    
    sort(cow_schedules.begin(), cow_schedules.end(), TimeComp);

    fin.close();

    fout << Solve(cow_schedules) << endl;

    fout.close();

    return 0;
}