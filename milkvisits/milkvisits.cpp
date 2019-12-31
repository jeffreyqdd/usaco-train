#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;

class DisjointSet
{
private:
    vector<int> p, rank, size;
    int numSets;
public:
    DisjointSet(int n)
    {
        p.assign(n,0); rank.assign(n,0); size.assign(n,1); numSets = n;
        for(int i = 0; i < p.size(); i++) p[i] = i;
    }

    int root(int i)
    {
        return (p[i] == i) ? i : (p[i] = root(p[i]));
    }

    bool find(int i, int j)
    {
        return root(i) == root(j);
    }
    
        
    void combine(int i, int j)
    {
        if(!find(i,j))
        {
            numSets --;

            int x = root(i), y = root(j);
            if(rank[x] > rank[y])
            {
                p[y] = x;
                size[y] += size[x];
            }
            else
            {
                p[x] = y;
                size[x] += size[y];
                if(rank[x] == rank[y]) rank[y]++;
            }
            

        }
    }

    int num_disjoint_sets()
    {
        return numSets;
    }
    int size_of(int i)
    {
        return size[root(i)];
    }
};

int main()
{
    ifstream fin("milkvisits.in");
    ofstream fout("milkvisits.out");


    int N, M; fin >> N >> M;
    string s; fin >> s;
    map<int, char> type;
    //construct the map
    for(int i = 0; i < s.size(); i++)
       type[i] = s[i]; 

    //for(auto o : type)
        //cout << o.first << " " << o.second << endl;
    
    
    DisjointSet dj(N);
    for(int i = 0; i < N - 1; i++)
    {
        int a, b; fin >> a >> b;

        --a; --b;

        if(type[a] == type[b])
        {
            //cout << "combining: " << a << " " << b << endl;
            dj.combine(a,b);
        }
    }

    string answer = "";
    for(int i = 0; i < M; i++)
    {
        int a, b; char c; fin >> a >> b >> c;
        --a; --b;

        //cout << "entering: " << a << " " << b << endl;
        //case 1..direct path from a to b...true if c == type[a]
        if(dj.find(a,b))
        {
            if(type[a] == c)
                answer+="1";
                //cout << "   true\n";
            else
                answer += "0";
                //cout << "   false\n";
        }
        else        //case 2..indirect path from a to b ..always true
        {
            answer += "1";
            //cout << "   true\n";
        }
        
        
        
    }

    fout << answer << endl;

    return 0;  
}
