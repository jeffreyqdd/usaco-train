/*
ID: jeffrey66
TASK: milk2
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;



enum EventType {start, stop};

struct milkEvent{ //basically startTime and stopTime (st/sp) and times
    int time;
    EventType type;
};

bool comp(milkEvent a, milkEvent b){
    if(a.time == b.time) return a.type < b.type;
    else; return a.time < b.time;
}

void solve(vector<milkEvent> milkTimes,int& maxMilk, int& maxIdle){
    int cnt = 0 ;
    int startTime = milkTimes[0].time;
    int stopTime = 0;



    for(auto i : milkTimes){
        if(i.type == start){
            cnt ++;
        }else cnt --;
        
        

        if(cnt == 1 && i.type == start){
            
            //startTime of milkEvent


            stopTime = i.time;

            maxIdle = max(maxIdle, stopTime - startTime);

            startTime = stopTime;
        }
        if(cnt == 0){
            //end of milkEvent
            
            stopTime = i.time;

            
            maxMilk = max(maxMilk, stopTime - startTime);

            startTime = stopTime;
            
        } 
    }
}

int main(){
    ifstream fin("milk2.in");
    ofstream fout("milk2.out");

    int n;

    fin >> n;

    vector<milkEvent> milkTimes;


    int m; 
    for (int i = 0; i<n; i++){
        
        fin >> m;

        milkTimes.push_back({m,start});

        fin >> m;
        milkTimes.push_back({m,stop});

    }

    fin.close();

    sort(milkTimes.begin(), milkTimes.end(), comp);

    int maxMilk;
    int maxIdle;
    solve(milkTimes, maxMilk, maxIdle);
    /*
    for (auto i : milkTimes) cout << i.time << " ";
    cout << endl;

    for (auto i : milkTimes) cout << i.type << " ";
    cout << endl;
    */
    fout << maxMilk << " " << maxIdle << endl;

    

    fout.close();
    return 0;
}