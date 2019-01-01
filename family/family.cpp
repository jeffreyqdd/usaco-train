#include <iostream>
#include <fstream>
using namespace std;

int kAncestor;
string mother[100], child[100];

string Mother(string const &daughter)
{
    for (int i = 0; i < kAncestor; i++)
    {
        if (child[i] == daughter)
            return mother[i];
    }
    return "";
}

int IsAncestor(string cow_a, string cow_b)
{
    int count = 0;
    while (cow_b != "")
    {
        if (cow_a == cow_b)
            return count;
        count++;
        cow_b = Mother(cow_b);
    }
    return -1;
}
void GetDist(int &dist1, int &dist2, string const &bessie, string const &elsie)
{

    string cow_a = bessie, cow_b = elsie;

    while (cow_a != "")
    {
        int count = IsAncestor(cow_a, cow_b);

        if (count != -1)
        {
            dist1 = count;
            return;
        }

        cow_a = Mother(cow_a);
        dist2++;
    }

    dist1 = dist2 = -1;

    return;
}
int main()
{
    ifstream fin("family.in");
    ofstream fout("family.out");

    string bessie, elsie;
    fin >> kAncestor >> bessie >> elsie;

    for (int i = 0; i < kAncestor; i++)
    {
        fin >> mother[i] >> child[i];
    }

    int dist1 = 0, dist2 = 0;

    GetDist(dist1, dist2, bessie, elsie);

    if (dist1 == -1 && dist2 == -1)
    {
        fout << "NOT RELATED\n";
    }
    else if (dist1 == 1 && dist2 == 1)
    {
        fout << "SIBLINGS\n";
    }
    else if (dist1 > 1 && dist2 > 1)
    {
        fout << "COUSINS\n";
    }
    else
    {
        if (dist1 > dist2)
        {
            swap(elsie, bessie);
            swap(dist1, dist2);
        }

        fout << elsie << " is the ";

        for (int i = 0; i < dist2 - 2; i++)
            fout << "great-";

        if (dist2 > 1 && dist1 == 0)
            fout << "grand-";

        if (dist1 == 0)
            fout << "mother";
        else
            fout << "aunt";

        fout << " of " << bessie << '\n';
    }

    fout.close();
    return 0;
}