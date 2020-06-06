#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    string A, B;
    cin >> A >> B;

    for(int i = 0; i < A.length(); i++)
    {
        A[i] = tolower(A[i]); B[i] = tolower(B[i]);

        if(A[i] < B[i])
        {
            cout << -1 << endl;
            return 0;
        }
        else if(B[i] < A[i])
        {
            cout << 1 << endl;
            return 0;
        }
    }
    cout << 0 << endl;
    return 0;
}