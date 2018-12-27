#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int kCows, order[101];

int BubbleSort()
{
    int moves = 0;
    vector<int> sort_log[2];

    for (int i = 0; i < kCows; i++)
    {
        for (int j = 0; j < kCows - 1; j++)
        {
            if (order[j] > order[j + 1])
            {
                sort_log[0].push_back(order[j]);
                sort_log[1].push_back(order[j + 1]);

                swap(order[j], order[j + 1]);
                moves++;
            }
        }
    }

    for (int i = 0; i < sort_log[0].size(); i++)
    {
        cout << sort_log[0][i] << "-" << sort_log[1][i] << endl;
    }

    int prev1, prev2, repeat1 = 0, repeat2 = 0;
    for (int i = 1; i < sort_log[0].size(); i++)
    {
        prev1 = sort_log[0][i - 1];
        prev2 = sort_log[1][i - 1];

        if (prev1 == sort_log[0][i])
            repeat1++;
        if (prev2 == sort_log[1][i])
            repeat2++;
    }
    cout << repeat1 << "---" << repeat2 << endl;

    return moves - min(repeat1, repeat2);
}

int main()
{
    ifstream fin("outofplace.in");
    ofstream fout("outofplace.out");

    fin >> kCows;

    for (int i = 0; i < kCows; i++)
        fin >> order[i];

    fin.close();

    fout << BubbleSort() << endl;

    fout.close();
}