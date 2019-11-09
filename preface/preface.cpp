/*
ID: jeffrey66
TASK: preface
LANG: C++11
*/


#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

string letter[] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D",  "CM", "M"};
int number[] =    {1,    4 ,   5,   9,   10,   40,   50,  90,  100,  400, 500,  900, 1000};


string recurse(int value, string numeral) //build recursively and greedily. 
{
    if(value == 0)
        return numeral;

    int i;
    for(i = 12; i >= 0; i--)
        if(value - number[i] >= 0)
            break;

    return recurse(value - number[i], numeral + letter[i]);
}


int main()
{
    ifstream fin("preface.in");
    ofstream fout("preface.out");

    int N; fin >> N; fin.close();



    int cnt[7] = {};
    char arr[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    for(int i = 1; i <= N; i++)
    {
        string rm = recurse(i, "");
        
        for(char s : rm)
            for(int j = 0; j < 7; j++)
                if(arr[j] == s)
                    cnt[j]++;
    }

    for(int i = 0; i < 7; i++)
    {
        if(cnt[i] != 0)
            fout << arr[i] << " " << cnt[i] << endl;
    }

    fout.close();


    return 0;
}