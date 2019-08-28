/*
ID: jeffrey66
TASK: subset
LANG: C++11
*/
#include <iostream>
#include <fstream>
using namespace std;

//simple recursion
void recurse(int num, int sum, int N, int half, int& cnt)
{
    if(sum == half)
    {
        cnt+= 1;
        //cout << "here\n";
        return;
    }
    else if(sum > half)
        return;
    else if(num > N)
        return;
    //cout << num << " : " << sum << endl;
    
    sum += num;
    recurse(num + 1, sum, N, half, cnt);
    sum -= num;
    recurse(num + 1, sum, N, half, cnt);
}
int main()
{
    ifstream fin("subset.in");
    ofstream fout("subset.out");

    int N; fin >> N;
    fin.close();


    //we just need to find subsets that add up to half the sum
    int half = N*(N+1) / 4, cnt = 0;
    recurse(1, 0, N, half, cnt); 

    fout << cnt/2 << endl;
    fout.close();
    return 0;
}