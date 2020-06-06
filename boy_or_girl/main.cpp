#include <iostream>
#include <set>
using namespace std;

int main()
{
    string s; cin >> s;
    set<char> unique(s.begin(), s.end());

    cout << (unique.size() % 2 == 1 ? "IGNORE HIM!" : "CHAT WITH HER!") << endl; 
    return 0;
}