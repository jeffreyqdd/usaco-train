#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>
#include <cmath>
using namespace std;

struct Peak
{
    int x;
    int y;

    //sort by tallest left most
    bool operator<(const Peak &p) const{
        if(y == p.y)
            return x < p.x;
        return y > p.y;
    }
};

bool CanSee(Peak a, Peak b)
{
    int dist = abs(a.x-b.x);
    //cout << dist << endl;
    if(a.y - dist < b.y)
        return true;
    return false;
}

int Solve(set<Peak> peak)
{
    //continue to call until peak is empty
    int size_before = 0, size_after = 1, erased = 0;

    while(!peak.empty())
    {
        Peak alpha_p = *peak.begin(); peak.erase(peak.begin());
        size_before = peak.size();


        set<Peak> will_erase;
        for(auto p : peak)
        {
            if(!CanSee(alpha_p, p))
            {
                cout << "delete";
                erased ++;
                will_erase.insert(p);
                if (peak.size() == 0) break;
            }
            cout << endl;
        }

        for(auto we : will_erase)
            peak.erase(we);


        size_after = peak.size();
    }

    return erased;
}

int main()
{
    ifstream fin("mountains.in");
    ofstream fout("mountains.out");

    int kMountains;
    fin >> kMountains;

    set<Peak> mountain_p;
    for(int i=0; i<kMountains; i++)
    {
        int x, y; fin >> x >> y;
        mountain_p.insert({x,y});
    }
    //cout << "here\n";
    
    fout << kMountains - Solve(mountain_p) << endl;

    return 0;
}