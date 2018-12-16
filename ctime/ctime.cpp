#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream fin("ctime.in");
    ofstream fout("ctime.out");

    int d, h, m;
    fin >> d >> h >> m;
    fin.close();

    int day_diff = d - 11;
    int hour_diff = h - 11;
    int minute_diff = m - 11;

    //mins in a day; 24 * 60 =  1440 minutes
    //mins in a hour = 60 minutes

    fout << max(-1, day_diff * 1440 + hour_diff * 60 + minute_diff) << endl;
    fout.close();
    return 0;
}