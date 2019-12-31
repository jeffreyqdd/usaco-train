#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define all(x) begin(x), end(x)

struct Cow
{
    int w,x,d;
    
    bool operator<(const Cow& c) const{
        return x < c.x;
    }
};

int N, L;
vector<Cow> cows;


int getTime()
{
    //contains position of cows that should go to each barn;
    vector<int> left_barn, right_barn;

    for(auto cow : cows)
    {
        if(cow.d == -1) left_barn.push_back(cow.x);
        else right_barn.push_back(cow.x);
    }   
    
    vector<pair<int,int>> combined; // combines them {distance, weight};

    for(int i = 0; i < left_barn.size(); i++)
    {
        combined.push_back({left_barn[i], cows[i].w});
    }

    for(int i = 0; i < right_barn.size(); i++)
    {
        
        combined.push_back({L - right_barn[i], cows[left_barn.size() + i].w});
    }
    sort(all(combined));
    /*for(auto p : combined)
    {
        cout << "dist: " << p.first << " weight: " << p.second << endl; 
    }*/

    int tot = 0; for(auto p : combined) tot += p.second;

    for(auto p : combined)
    {
        tot -= 2 * p.second;
        if(tot <= 0) return p.first;
    }


    return 0;
}


int main()
{
    ifstream fin("meetings.in");
    ofstream fout("meetings.out");

    fin >> N >> L;

    cows.resize(N);
    for(auto& o : cows)
        fin >> o.w >> o.x >> o.d;

    sort(all(cows));

    int time = getTime();

    //cout << time << endl;

    int ans = 0;
    queue<int> q;
    for(int i = 0; i < N; i++)
    {
        if(cows[i].d == -1)
        {
            while(!q.empty() && q.front() + 2 * time < cows[i].x) q.pop();
            ans += q.size();
        }
        else
        {
            q.push(cows[i].x);
        }
    } 

    fout << ans << endl;

    return 0;

}