#include <iostream>
#include <fstream>
using namespace std;

int GetDist(int a, int b)
{

    return max(a, b) - min(a, b);
}
int main()
{
    ifstream fin("teleport.in");
    ofstream fout("teleport.out");

    int a, b, x, y;
    fin >> a >> b >> x >> y;
    fin.close();

    //write the minimum distance between no teleport and use teleport from both
    fout << min(GetDist(a, b), min(GetDist(a, x) + GetDist(b, y), GetDist(a, y) + GetDist(b, x))) << endl;
    fout.close();

    return 0;
}