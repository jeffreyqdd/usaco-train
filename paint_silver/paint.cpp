#include <iostream>
#include <fstream>
using namespace std;

//just a side note: this is animal abuse farmer john..you should be ashamed of yourself

#define MAX_N 100001

struct Event
{
    int x;
    int layer; 
    
    bool operator<(const Event &e) const
    {
        return x < e.x;
    }
};


Event event[MAX_N];

int main()
{
    ifstream fin("paint.in");
    ofstream fout("paint.out");

    int kMoves, kLayers; fin >> kMoves >> kLayers;

    int currLoc = 0;
    for(int i = 0; i < kMoves; i++)
    {
        int move; char dir; fin >> move >> dir;
        
        int newLoc = currLoc + move * (dir == 'L'? -1 : 1);

        event[i*2].x = min(currLoc, newLoc);
        event[i*2].layer = 1;

        event[i*2 + 1].x = max(currLoc, newLoc);
        event[i*2 + 1].layer = -1;

        currLoc = newLoc;
    }   



    //traverse and solve;
    sort(event, event + 2 * kMoves);

    int currLayers = 0;
    int answer = 0;
    
    for(int i = 0; i < kMoves * 2; i++)
    {
        if(i > 0 && currLayers >= kLayers)
            answer += event[i].x - event[i-1].x;

        currLayers += event[i].layer;
    }

    fout << answer << endl;



    return 0;
}