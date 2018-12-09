#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

bool IsDebug = true;

/* 
Input format
N M D S     # of people - # of samples - # of drinkings - # of sick
P M T       person who drank - which sample of milk - at what t
. . .       
. . .
p t         person who got sick - t of sickness
. .

--assigned ids from [1,A]

Output:
N # of medications, min amount to be able to treat worst case scenario(most # of people get sick)
*/

struct Round
{
    int p;
    int m;
    int t;

    bool operator<(const Round &r) const
    {
        return t < r.t;
    }
};

struct Sick
{
    int p;
    int t;

    bool operator<(const Sick &s) const
    {
        return t < s.t;
    }
};

int kPeople, kSamples, kRounds, kSick;
vector<Round> rounds;
vector<Sick> sick;

int solve()
{
    map<int, int> suspicious_milk; //maps milkID to # of occurrences
    int max_milk = 0;              //counter remebering the highest occurence of milk poisoning done by a single milk.

    //vector rounds (containing the the milk drinking) is already sorted based on time [start, stop]
    //vector sick (people who got sick) is already sorted based on time as well [early sick, late sick]

    //do a iteration for every person who got sick and keep track of the milk they drank up until that specific instance
    for (int i = 0; i < kSick; i++)
    {
        int person_id = sick[i].p;
        int time_sick = sick[i].t;
        //iterating up until time sick
        for (int j = 0; j < kRounds; j++)
        {
            if (rounds[j].t >= time_sick)
                break;

            if (rounds[j].p == person_id)
            {
                if (suspicious_milk.find(rounds[j].m) != suspicious_milk.end())
                {
                    //found
                    suspicious_milk[rounds[j].m] += 1;
                    max_milk = max(max_milk, suspicious_milk[rounds[j].m]);
                }
                else
                {
                    //not found
                    suspicious_milk[rounds[j].m] = 1;
                    max_milk = max(max_milk, suspicious_milk[rounds[j].m]);
                }
            }
        }
    }

    if (IsDebug)
        for (auto m : suspicious_milk)
            cout << m.first << "--" << m.second << endl;

    //only the milks ids with #of occurrences that = max_milk are recorded
    vector<int> verified_bad;

    for (auto m : suspicious_milk)
    {
        if (m.second == max_milk)
            verified_bad.push_back(m.first);
    }

    if (IsDebug)
    {
        cout << "here is max_milk:" << max_milk << endl;
        cout << "here are the verified bad milks\n";
        for (auto m : verified_bad)
            cout << m << "--";
        cout << endl;
    }

    set<int> sick_people;
    //we then do a final count iterating down the rounds once again detecting who drank the bad milk, the set data structure has unique points so
    //we just insert the people who drank the bad milks and take set.size()
    for (auto r : rounds)
    {
        for (auto milk_id : verified_bad)
        {
            if (r.m == milk_id)
                sick_people.insert(r.p);
        }
    }

    if (IsDebug)
    {
        cout << "here are the detected sick people\n";
        for (auto s : sick_people)
            cout << s << "-";
        cout << endl;
    }
    return sick_people.size();
}

int main()
{
    ifstream fin("badmilk.in");
    ofstream fout("badmilk.out");

    fin >> kPeople >> kSamples >> kRounds >> kSick;

    for (int i = 0; i < kRounds; i++)
    {
        int p, m, t;
        fin >> p >> m >> t;
        rounds.push_back({p, m, t});
    }

    for (int i = 0; i < kSick; i++)
    {
        int p, t;
        fin >> p >> t;
        sick.push_back({p, t});
    }
    fin.close();

    sort(rounds.begin(), rounds.end());
    sort(sick.begin(), sick.end());

    if (IsDebug)
    {
        for (auto s : rounds)
            cout << "(" << s.p << "," << s.m << "," << s.t << ")" << endl;
        for (auto s : sick)
            cout << "(" << s.p << "," << s.t << ")" << endl;
    }

    fout << solve() << endl;

    return 0;
}