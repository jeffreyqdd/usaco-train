#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

#define N 1000


int main()
{
    srand(time(0));



    int a = 1,b = 76,c = 10;

    for(int i = 0; i < c; i++)
    {
        cout << rand() % (b - a + 1) << endl;
    }

    
    return 0;
}