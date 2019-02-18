#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;



int main()
{
    ifstream fin("lemonade.in");
    ofstream fout("lemonade.out");

    int kCows;

    fin >> kCows;

    vector<int> line(kCows);

    for(auto &o : line)
        fin >> o;

    sort(line.rbegin(), line.rend());

    int min_cow = 0;
    for(int i = 0; i < line.size(); i++)
        if(i > line[i])
        {
            min_cow = i;
            break;
        }
    if(min_cow == 0) fout << kCows << endl;
    else fout << min_cow << endl;

    fout.close();

    return 0;
}