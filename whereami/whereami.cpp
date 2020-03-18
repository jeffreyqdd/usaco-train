#include <fstream>
#include <set>
#include <string>
using namespace std;


int N;
string S;

bool duplicate(int len)
{
    set<string> repeat;
    for(int i = 0; i <= S.length() - len; i++)
    {
        if(repeat.count(S.substr(i, len)) > 0) return true;
        repeat.insert(S.substr(i,len));
    }

    return false;
}

int main()
{
    ifstream fin("whereami.in");
    ofstream fout("whereami.out");

    fin >> N >> S;

    int ans = 1;

    while(duplicate(ans)) ans++;

    fout << ans << endl;

    return 0;
}