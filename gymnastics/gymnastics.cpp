#include <iostream>
#include <fstream>
using namespace std;

#define MAX_K 15
#define MAX_N 25

int K, N, sessions[MAX_K][MAX_N];


bool isBefore(int a, int b, int s)
{
    int i, j;

    for(int cow = 1; cow <= N; cow++)
    {
        if(sessions[s][cow] == a) i = cow;
        if(sessions[s][cow] == b) j = cow;
    }

    return i < j;
}

bool isConsistent(int cowA, int cowB)
{
    for(int s = 1; s <= K; s++)
    {
        if(!isBefore(cowA,cowB,s))
            return false;
    }
    return true;
}

int main()
{
    ifstream fin("gymnastics.in");
    ofstream fout("gymnastics.out");

    fin >> K >> N;

    for(int r = 1; r <= K; r++)
    {
        for(int c = 1; c <= N; c++)
        {
            fin >> sessions[r][c];
            //cout << sessions[r][c] << " ";
        }
        //cout << endl;
    }

    int answer = 0;

    for(int cowA = 1; cowA <= N; cowA++)
    {
        for(int cowB = 1; cowB <= N; cowB++)
        {
            if(cowA != cowB)
            {
                //process
                if(isConsistent(cowA,cowB)) answer++;
            }
        }
    }
    
    fout << answer << endl;

    return 0;
}