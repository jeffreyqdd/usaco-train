#include <iostream>
#include <fstream>
using namespace std;

int test(int number, int goal)
{
    return goal - (number - (number / 3) - (number / 5) + (number / 15));
}
int main()
{
    ifstream fin("moobuzz.in");
    ofstream fout("moobuzz.out");

    int N; fin >> N;

    int ret = 0;
    

    for(ret = 1; ;)
    {
        int delta = test(ret, N);

        //cout << ret << ", " << delta<< endl;
        
        if(delta == 0) break;
        

        ret += delta;

       
    }

    fout << ret << endl;


    return 0;
}