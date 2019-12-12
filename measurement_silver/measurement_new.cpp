#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
using namespace std;

struct Event
{
    int day, cow, delta;
    Event(){}
    Event(int day, int cow, int delta): day(day), cow(cow), delta(delta) {}
    bool operator<(const Event &e) const {return day < e.day;}
};

int main()
{
    ifstream fin("measurement.in");;
    ofstream fout("measurement.out");

    int N, G; fin >> N >> G;

    vector<Event> events(N);

    for(auto& o : events)
        fin >> o.day >> o.cow >> o.delta;

    fin.close();

    sort(events.begin(), events.end());
        

    map<int, int, greater<int>> cnts;
    cnts[0] = N + 1;

    int result = 0;
    map<int,int> cows;

    for(auto& e : events)
    {

        
        for(auto m : cnts)
            cout << m.first << " " << m.second << endl;
        
        cout << "entering: " << e.day << " " << e.cow << " " << e.delta << endl;
        
        
        int& ref = cows[e.cow];
        bool wastop = ref == cnts.begin() -> first;
        int wascnt = cnts[ref] --;

        cout << "   before change: " << ref << endl;
        cout << "   was top: " << wastop << endl;
        cout << "   was cnt: " << wascnt << endl;



        if(wascnt == 1)
            cnts.erase(ref);


        ref += e.delta;
    
        int iscnt = ++cnts[ref];
        bool istop = ref == cnts.begin()->first;

        cout << "   after change: " << ref << endl;
        cout << "   iscnt: " << iscnt << endl;
        cout << "   istop: " << istop << endl;


        if (wastop) {
        if (!istop || wascnt != 1 || iscnt != 1) {
            ++result;
        }
        } else if (istop) {
            ++result;
        }
    
    }

    cout << result << endl;

}