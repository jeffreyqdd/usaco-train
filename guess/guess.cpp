#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <iterator>
using namespace std;


struct Characteristics
{
    string name;
    int num;
    vector<string> traits;
};
vector<Characteristics> animals;
int kEntries;

//brutal force
//compare each animal with every other animal
int GetSimilar(Characteristics const &a, Characteristics const &b)
{
    int count = 0;
    set<string> seen;
    //how similar between a and b
    for(auto t : b.traits)
        seen.insert(t);

    for(auto t : a.traits)
        if(seen.find(t) != seen.end())
            count++;

    //one more "yes" question to break tie?
    if(count < a.traits.size())
        count++;
    
    return count;
}

int Solve()
{
    int max_yes = 0;
    for(int i = 0; i < kEntries; i++)
    {
        for(int j = 0; j < kEntries; j++)
        {
            if (i == j) continue;

            max_yes = max(max_yes, GetSimilar(animals[i], animals[j]));   
        }
    }

    return max_yes;
}
int main()
{
    ifstream fin("guess.in");
    ofstream fout("guess.out");

    fin >> kEntries;

    for(int i = 0; i < kEntries; i++)
    {
        string name; int num;
        fin >> name >> num;
        vector<string> v;
        for(int j = 0; j < num; j++)
        {
            string s; fin >> s;
            v.push_back(s);
        }

        animals.push_back({name,num,v});
    }
    fin.close();

    fout << Solve() << endl;

    fout.close();

    return 0;
}