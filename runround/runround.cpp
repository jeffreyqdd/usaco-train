/*
ID: jeffrey66
TASK: runround
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

typedef unsigned long ul;

bool isRunRoundNum(ul num)
{
    int repeat[10] = {}, split[20] = {}, seen[20] = {}, sum = 0, length = to_string(num).length();

    //split
    //cout << "num: " << num << " length: " << length <<  endl;
    for(int n = num, i = length - 1; n >= 0 && i >= 0; i--, n /= 10)
    {
        int digit = n % 10;
        //check zero
        if(digit == 0) return false;
        //check if repeat
        if(repeat[digit] == 1) return false;
        repeat[digit] += 1;
        //split
        split[i] = digit;
        sum += digit;
    }

    
    for(int curr = 0, cnt = 0; ; cnt++)
    {
        //check if seen
        if(seen[curr] != 0) break;
        //mark as seen
        seen[curr] = 1;

        //do a step
        curr = (curr + split[curr]) % length;

        if(curr == 0 && cnt == length - 1) return true;

        //cout << "cnt= "<<cnt << ", curr ="<<curr << endl;
    }

    return false;
}



int main()
{
    ifstream fin("runround.in");
    ofstream fout("runround.out");

    ul M; fin >> M; fin.close();

    ul i;

    for(i = M + 1;;i++)
        if(isRunRoundNum(i))
            break;

    fout << i << endl;
    fout.close();

    return 0;
}