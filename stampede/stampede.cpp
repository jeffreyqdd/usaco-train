#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

struct Cow
{
    int x,y,r,start,stop;

    Cow(int start_x, int start_y, int start_r)
    {
        x = start_x; y = start_y; r = start_r;

        start = (x * -r) - r;
        stop =  (x * -r);
    }
    bool operator<(const Cow& c) const
    {
        if(start == c.start) return stop < c.stop;
        else return start < c.start;
    }
};

int solve(const vector<Cow>& race)
{
    int cnt = 0;

    

    return cnt;
}

int main()
{
    ifstream fin("stampede.in");
    ofstream fout("stampede.out");

    int kCows; fin >> kCows;

    vector<Cow> race;
    for(int i = 0; i < kCows; i++)
    {
        int x,y,r; fin >> x >> y >> r;
        race.push_back(Cow(x,y,r));
    }
    sort(race.begin(), race.end());

    cout << solve(race) << endl;

    fin.close();
    fout.close();
    return 0;
}
