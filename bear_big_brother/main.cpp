#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double a, b, day = 0; cin >> a >> b;


    while (a * pow(3,day) <= b * pow(2,day))
        day++;

    cout << day << endl;
    return 0;
}