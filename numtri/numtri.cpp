/*
ID: jeffrey66
TASK: numtri
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <queue>
using namespace std;

int kRows;
vector<pair<int, int>> adj[500500];
priority_queue<pair<int, int>> q;

int main()
{
    ifstream fin("numtri.in");
    ofstream fout("numtri.out");

    int num_count = 0;
    fin >> kRows;

    int total_num;
    for (int r = 0; r < kRows; r++)
    {
        for (int c = 0; c <= r; c++)
        {
            int weight;
            fin >> weight;
            adj[num_count].push_back({num_count + r + 1, weight});
            adj[num_count].push_back({num_count + r + 2, weight});
            total_num = num_count + r + 2;
            num_count++;
        }
    }
    vector<int> distance;
    vector<bool> processed;
    for (int i = 0; i < total_num; i++)
    {
        distance.push_back(numeric_limits<int>::min());
        processed.push_back(false);
    }

    distance[0] = 0;
    q.push({0, 0});

    while (!q.empty())
    {
        int a = q.top().second;
        q.pop();
        if (processed[a])
            continue;
        processed[a] = true;

        for (auto u : adj[a])
        {
            int b = u.first, w = u.second;
            if (distance[a] + w > distance[b])
            {
                distance[b] = distance[a] + w;
                q.push({-distance[b], b});
            }
        }
    }

    for (auto d : distance)
        cout << d << " ";
    cout << endl;

    fin.close();

    fout << *max_element(distance.begin(), distance.end()) << endl;

    fout.close();
    return 0;
}