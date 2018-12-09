#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ifstream fin("square.in");
    ofstream fout("square.out");

    vector<int> x_coord;
    vector<int> y_coord;

    for (int i = 0; i < 4; i++)
    {
        int x, y;
        fin >> x >> y;
        x_coord.push_back(x);
        y_coord.push_back(y);
    }
    fin.close();

    sort(x_coord.begin(), x_coord.end());
    sort(y_coord.begin(), y_coord.end());

    int length1 = x_coord[x_coord.size() - 1] - x_coord[0];
    int length2 = y_coord[y_coord.size() - 1] - y_coord[0];

    fout << max(length1 * length1, length2 * length2) << endl;

    fout.close();
    return 0;
}
