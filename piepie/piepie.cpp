#include <iostream>
#include <fstream>
#include <queue>
#include <set>
using namespace std;

#define MAX_PIE 100000
#define INF 100000000
int bPie[MAX_PIE * 2] = {}, ePie[MAX_PIE * 2] = {};

int main()
{
    ifstream fin("piepie.in");
    ofstream fout("piepie.out");

    int kTotalPie, kMaxTasty; fin >> kTotalPie >> kMaxTasty;

    for(int i = 0; i < kTotalPie * 2; i++)
        fin >> bPie[i] >> ePie[i];

    fin.close();

    /*for(int i = 0; i < kTotalPie * 2; i++)
    {
        cout << bPie[i] << " " << ePie[i] << endl;
    }*/


    int distance[MAX_PIE * 2] = {};
    set<pair<int,int>> bessie, elsie;
    
    queue<int> q;
    
    for(int i = 0; i < 2 * kTotalPie; i++)
    {
        if(i >= kTotalPie) // bessie's pie
        {
            if(bPie[i] == 0)
            {
                distance[i] = 1; //start searc
                //cout << "meow\n";
                q.push(i);
            }
            else //push bessie's pref
            {
                distance[i] = INF;
                bessie.insert(make_pair(bPie[i],i));
            }
        }
        else // elsie's pie
        {
            if(ePie[i] == 0)
            {
                distance[i] = 1;
                //cout << "meow\n";
                q.push(i);
            }
            else
            {
                distance[i] = INF;
                elsie.insert(make_pair(ePie[i], i));
            }

        }
    }
    


    while(!q.empty())
    {
        int next = q.front(); q.pop();

        //check for if whether bessie or elsie

        if(next < kTotalPie) //bessie
        {
            auto it = bessie.lower_bound(make_pair(bPie[next] - kMaxTasty, -1));

            while(it != bessie.end() && bPie[it->second] <= bPie[next])
            {
                distance[it -> second] = distance[next] + 1;
                q.push(it -> second);
                it = bessie.erase(it);

                //cout << it -> second << endl;
            }
        }
        else //elsie
        {
            auto it = elsie.lower_bound(make_pair(ePie[next] - kMaxTasty, -1));

            while(it != elsie.end() && ePie[it -> second] <= ePie[next])
            {
                distance[it -> second] = distance[next] + 1;
                q.push(it -> second);
                it = elsie.erase(it);

                //cout << it -> second << endl;
            }
        }

    }

    for(int i = 0; i < kTotalPie; i++)
    {
        if(distance[i] == INF)
            fout << -1 << endl;
        else 
            fout << distance[i] << endl;
    }
    fout.close();
    return 0;
}