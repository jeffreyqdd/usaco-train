#include <iostream>
using namespace std;

int main()
{
    int N, a,b,c, total = 0;

    cin >> N;

    for(int i = 0; i < N; i++) {
        cin >> a >> b >> c;
        if(a + b + c >= 2) total++;
    }

    cout << total << endl;
    
    return 0;
}