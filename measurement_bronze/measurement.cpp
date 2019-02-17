#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Event
{
    string name;
    int day;
    int change;

    bool operator<(const Event &e) const
    {
        return day < e.day;
    }
};
struct Cow
{
    string s;
    int milk;
    bool operator<(const Cow &c) const
    {
        return milk <= c.milk;
    }
};
int kEvents;
string IsHighest(Cow b, Cow e, Cow m)
{

    vector<Cow> cows = {b, e, m};
    sort(cows.begin(), cows.end());

    if (cows[0].milk == cows[1].milk && cows[0].milk == cows[2].milk)
    {
        return "bem";
    }
    else if (cows[1].milk == cows[2].milk)
    {
        string s = cows[1].s + cows[2].s;
        sort(s.begin(), s.end());
        return s;
    }

    return cows[2].s;
}

int Solve(vector<Event> record)
{
    int change = 0;
    string display = "bem";
    int bessie = 7, elsie = 7, mildred = 7;

    for (auto r : record)
    {

        if (r.name == "Bessie")
        {
            bessie += r.change;
        }
        else if (r.name == "Elsie")
        {
            elsie += r.change;
        }
        else if (r.name == "Mildred")
        {
            mildred += r.change;
        }

        cout << bessie << "-" << elsie << "-" << mildred << endl;

        string wall = IsHighest({"b", bessie}, {"e", elsie}, {"m", mildred});
        cout << wall << endl;
        if (display != wall)
        {
            display = wall;
            change++;
            cout << "change" << endl
                 << endl;
        }
        else
            cout << "no" << endl
                 << endl;
    }
    return change;
}

int main()
{
    ifstream fin("measurement.in");
    ofstream fout("measurement.out");

    fin >> kEvents;
    vector<Event> record;
    for (int i = 0; i < kEvents; i++)
    {
        Event event;
        fin >> event.day >> event.name >> event.change;
        record.push_back(event);
    }

    fin.close();

    sort(record.begin(), record.end());

    fout << Solve(record) << endl;

    return 0;
}