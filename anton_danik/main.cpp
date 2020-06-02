#include <iostream>
using namespace std;

int N,a,d;
string S;

int main()
{
    cin >> N >> S;
    for(int i = 0; i < N; i++)
    {
        if(S[i] == 'A') a++;
        else d++;
    }

    if(a == d) cout << "Friendship\n";
    else cout << (a > d ? "Anton\n" : "Danik\n");

    return 0;
}