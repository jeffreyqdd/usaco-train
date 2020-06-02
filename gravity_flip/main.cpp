#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_N 100
int main()
{
    int A[100], N;

    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> A[i];
    }
    sort(A, A + N);

    for(int i = 0; i < N; i++)
        cout << A[i] << " ";
    cout << endl;
 
    return 0;
}