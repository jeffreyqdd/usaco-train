/*
ID: jeffrey66
TASK: numtri
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <limits>
#include <algorithm>
using namespace std;

int kRows;
//vector<pair<int, int>> adj[1005];
vector<tuple<int, int, int>> edges;

int main()
{
    ifstream fin("numtri.in");
    ofstream fout("numtri.out");

    int num_count = 0;
    fin >> kRows;

    int total_num;

    for (int r = 0; r < kRows; r++)
        for (int c = 0; c <= r; c++)
        {
            int weight;
            fin >> weight;
            //adj[num_count].push_back({num_count + r + 1, weight});
            //adj[num_count].push_back({num_count + r + 2, weight});
            edges.push_back({num_count, num_count + r + 1, weight});
            edges.push_back({num_count, num_count + r + 2, weight});
            total_num = num_count + r + 2;
            num_count++;
        }
    fin.close();

    // print out the edges

    for (auto e : edges)
    {
        int from, to, weight;
        tie(from, to, weight) = e;
        cout << '(' << from << ' ' << to << ' ' << weight << ')' << endl;
    }

    // shortest path using Bellman-Ford
    vector<int> distance;
    for (int i = 0; i < total_num; i++)
    {
        distance.push_back(numeric_limits<int>::min());
    }

    distance[0] = 0;

    for (int i = 0; i < total_num - 1; i++)
    {

        for (auto e : edges)
        {
            int a, b, w;
            tie(a, b, w) = e;
            distance[b] = max(distance[b], distance[a] + w);
        }
    }

    for (auto d : distance)
    {
        cout << d << " ";
    }
    cout << endl;

    fout << *max_element(distance.begin(), distance.end()) << endl;
    fout.close();
    return 0;
}