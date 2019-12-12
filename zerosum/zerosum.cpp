/*
ID: jeffrey66
TASK: zerosum
LANG: C++11
*/

#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("zerosum.in");
ofstream fout("zerosum.out");
int N;

int eval(string s)
{
    int sum = 0;
    int sign = 1;
    int digit = 0;
    
    for(int i = 0; i < s.length(); i++)
    {
        char c = s[i];
        
        switch(c)
        {
            case ' ':
                break;
            case '+':
                sum += digit * sign;
                sign = 1;
                digit = 0;
                break;
            case '-':
                sum += digit * sign;
                sign= -1;
                digit = 0;
                break;
            default:
                //digit
                digit = digit * 10 + (c - '0'); 

        }


        //cout << c << " ";
    }

    sum += digit * sign;

    //cout<<"= "<< sum << endl;

    return sum;
}


void generate(string arr, int k)
{
    string moves[] = {" ", "+", "-"};

    
    if(k == N - 1)
    {
        if(eval(arr) == 0)
            fout << arr << endl;
        return;
    }

    for(string m : moves)
    {
        arr[2 * k + 1] = m[0];
        //cout << m <<"," << k << endl;
        generate(arr, k + 1);
    }
}


int main()
{
    fin >> N;

    //cut the string
    string s = ((string)"1 2 3 4 5 6 7 8 9").substr(0,N * 2 - 1);

    //fprintf(fout, "%s\n", s.c_str());
    

    generate(s, 0);



    return 0;
}