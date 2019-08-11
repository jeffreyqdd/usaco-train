/*
ID: jeffrey66
TASK: pprime
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


//test if divisible by 2, 3, and 6k +- 1 
bool is_prime(int n)
{
    // Corner cases 
    if (n <= 1)  return false; 
    if (n <= 3)  return true; 
  
    // This is checked so that we can skip  
    if (n%2 == 0 || n%3 == 0) return false; 
  
    //only need to check to sqrt(n)
    for (int i=5; i*i<=n; i=i+6) 
        if (n%i == 0 || n%(i+2) == 0) 
           return false; 
  
    return true; 
}


int main()
{
    ifstream fin("pprime.in");
    ofstream fout("pprime.out");

    int a, b; fin >> a >> b; //[a,b]
    fin.close();
    
    if(a < 10)
    {
        //one digit
        for(int d1 = a; d1 < 10; d1++)
        {
            int pal = d1;

            if(pal > b) break;
            if(pal >= a && is_prime(pal)) fout << pal << endl;
        }
    }

    if(a < 100)
    {
        //two digit
        for(int d1 = 1; d1 < 10; d1+=2)
        {
            int pal = 10 * d1 + d1;

            if(pal > b) break;
            if(pal >= a && is_prime(pal)) fout << pal << endl;
        }
    }

    if(a < 1000)
    {
        //three digit
        for(int d1 = 1; d1 < 10; d1+=2)
        {
            for(int d2 = 0; d2 < 10; d2++)
            {
                int pal = 100 * d1 + 10 * d2 + d1;

                if(pal > b) break;
                if(pal >= a && is_prime(pal)) fout << pal << endl;
            }
        }
    }

    if(a < 10000)
    {
        //four digit
        for(int d1 = 1; d1 < 10; d1+=2)
        {
            for(int d2 = 0; d2 < 10; d2++)
            {
                int pal = 1000 * d1 + 100 * d2 + 10 * d2 + d1;
                //cout << pal << endl;
                if(pal > b) break;
                if(pal >= a && is_prime(pal)) fout << pal << endl;
            }
        }
    }
    if(a < 100000)
    {
        //five digit
        for(int d1 = 1; d1 < 10; d1+=2)
        {
            for(int d2 = 0; d2 < 10; d2++)
            {
                for(int d3 = 0; d3 < 10; d3++)
                {
                    int pal = 10000 * d1 + 1000 * d2 + 100 * d3 + 10 * d2 + d1;
                    if(pal > b) break;
                    if(pal >= a && is_prime(pal)) fout << pal << endl;
                }
            }
        }
    }
    if(a < 1000000)
    {
        //six digit
        for(int d1 = 1; d1 < 10; d1+=2)
        {
            for(int d2 = 0; d2 < 10; d2++)
            {
                for(int d3 = 0; d3 < 10; d3++)
                {
                    int pal = 100000 * d1 + 10000 * d2 + 1000 * d3+ 100 * d3 + 10 * d2 + d1;
                    if(pal > b) break;
                    if(pal >= a && is_prime(pal)) fout << pal << endl;
                }
            }
        }
    }
    if(a < 10000000)
    {
        //seven digit
        for(int d1 = 1; d1 < 10; d1+=2)
        {
            for(int d2 = 0; d2 < 10; d2++)
            {
                for(int d3 = 0; d3 < 10; d3++)
                {
                    for(int d4 = 0; d4 < 10; d4++)
                    {   
                        int pal = 1000000 * d1 + 100000 * d2 + 10000 * d3+ 1000 * d4 + 100 * d3 + 10 * d2 + d1;
                        if(pal > b) break;
                        if(pal >= a && is_prime(pal)) fout << pal << endl;
                    }
                }
            }
        }
    }
    if(a < 100000000)
    {
        //eight digit
        for(int d1 = 1; d1 < 10; d1+=2)
        {
            for(int d2 = 0; d2 < 10; d2++)
            {
                for(int d3 = 0; d3 < 10; d3++)
                {
                    for(int d4 = 0; d4 < 10; d4++)
                    {   
                        int pal = 10000000 * d1 + 1000000 * d2 + 100000 * d3+ 10000 * d4 + 1000 * d4 + 100 * d3 + 10 * d2 + d1;
                        if(pal > b) break;
                        if(pal >= a && is_prime(pal)) fout << pal << endl;
                    }
                }
            }
        }
    }

    fout.close();
    return 0;
}