#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Cow
{
    int weight, dir;
    double loc;

    Cow(){}
    Cow(int weight, double loc, int dir): weight(weight), loc(loc), dir(dir){}
    
    void walk(double time)
    {
        loc += time * dir;
    }

    void flip()
    {
        dir *= -1;
    }

    bool operator<(const Cow& c) const{
        return loc < c.loc;
    }
};


int simulate(vector<Cow>& line, int L, int totalWeight)
{    

    int currWeight = 0;
    double runningT = 0;
    int collisions = 0;
    while((double) currWeight / (double) totalWeight < 0.5)
    {
        double bestT = 1 << 30;
        
        for(int i = 0; i < line.size(); i++)
        {
            //check ends
            if(i == 0 && line[i].dir == -1) bestT = min(bestT, line[i].loc);
            if(i == line.size() - 1 && line[i].dir == 1) bestT = min(bestT, L - line[i].loc);

            if(i < line.size() - 1)
            {
                if(line[i].dir == 1 && line[i+1].dir == -1 && line[i].loc != line[i+1].loc)
                {
                    //facing opposites and newly collided
                    double etaCollision = (line[i + 1].loc - line[i].loc) / 2.0;

                    bestT = min(bestT, etaCollision);

                }
            }

            if(bestT == 0.5) break;

        }

        //simulate()
        for(int i = 0; i < line.size(); i++)
        {
            line[i].walk(bestT);

            if(i > 0 && line[i].loc == line[i - 1].loc)
            {
                line[i].flip();
                line[i - 1].flip();
                collisions++;
            }

        }
        
        if(line[0].loc == 0)
        {
            currWeight += line[0].weight;
            line.erase(line.begin());
        }
        if(line[line.size() - 1].loc == L)
        {
            currWeight += line[line.size() - 1].weight;
            line.erase(--line.end());
        }
        /*cout << runningT <<endl;
        for(auto o : line)
        {
            cout << o.loc << " " << (o.dir == 1? "->" : "<-") << endl;
        }
        cout <<endl;*/
    }
    return collisions;
}

int main()
{
    ifstream fin("meetings.in");
    ofstream fout("meetings.out");

    int N, L; fin >> N >> L;

    vector<Cow> line(N);

    int total = 0;
    for(auto& o : line)
    {
        fin >> o.weight >> o.loc >> o.dir;
        total+=o.weight;
    }

    sort(line.begin(), line.end());
    
    fout << simulate(line, L, total) << endl;

    return 0;
}