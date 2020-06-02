#include <iostream>
using namespace std;

int main()
{
    int N, H, x, ans = 0;
    cin >> N >> H;
    for(int i = 0; i < N; i++)
    {
        cin >> x;
        if(x > H) ans += 2;
        else ans += 1;
    }

    cout << ans << endl;
    
    return 0;
}