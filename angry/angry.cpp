#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define INF 2000000000


int main()
{
    ifstream fin("angry.in");
    ofstream fout("angry.out");

    int kBales; fin >> kBales;
    vector<int> field(kBales);
    for(auto &o : field) fin >> o;
    fin.close();

    sort(field.begin(), field.end());

    int beg = 0;
    int radL = 0;
    int end = kBales - 1;
    int radR = 0;

    double best = INF;

    while(true)
    {
        
    }

    return 0;
}