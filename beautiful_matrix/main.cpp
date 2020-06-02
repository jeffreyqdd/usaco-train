#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int N = 0,r,c;
    for(r = 1; r <= 5; r++)
    {
        for(c = 1; c <= 5; c++)
        {
            cin >> N;
            if(N == 1) break;
            
        }
        if(N == 1) break;
    }

    //manhattan distance to 3,3
    cout << abs(r - 3) + abs(c - 3) << endl;

    return 0;
}