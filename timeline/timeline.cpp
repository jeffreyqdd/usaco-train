#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

struct Event
{
    int a, b, x;
};

int MAX = 100000;

vector<int> earliest;
map<long long, Event> constraints;
vector<long long> keys;


//set<long long> seen;

void proc_event(Event c) {

        // update current one
        earliest[c.b] = max(earliest[c.b], earliest[c.a] + c.x);
        //cout << c.a << endl;
        // find all keys that depend on b
        for (auto k : keys) {
            if ( k > c.b * MAX && k < (c.b + 1) * MAX ) {
                 //if(seen.find(k) == seen.end())
                 //{
                    //seen.insert(k);
                    proc_event(constraints[k]);  
                 //} 
            }
        }


}

int main()
{
    ifstream fin("timeline.in");
    ofstream fout("timeline.out");

    int N, M, C;
    fin >> N >> M >> C;

    earliest.push_back(-1); // [0] not used

    // [0] not used
    for(int i = 0; i < N; i++)
    {
        int s; 
        fin >> s; 
        earliest.push_back(s);
    }


    for(int i = 0; i < C; i++)
    {
        int a,b,x; 
        fin >> a >> b >> x;
        long long k = a * MAX + b;
        constraints[k] = {a,b,x};
        keys.push_back(k);
    }

    sort(keys.begin(),keys.end());

    for (auto k : keys) {
        
        proc_event (constraints[k]);
       
    }

    
    for(int i=0; i< N; i++)
    {
        fout << earliest[i+1] << endl;
    }

    return 0;
}