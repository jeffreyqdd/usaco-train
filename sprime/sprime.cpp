/*
ID: jeffrey66
TASK: sprime
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;



bool IsPrime(int n)
{

    // Corner cases 
    if (n <= 1)  return false; 
    if (n <= 3)  return true; 
  
    //according to wikipedia, factors of numbers can only be of:
    //2, 3, 6k +- 1  
    if (n%2 == 0 || n%3 == 0) return false; 
  
    //only need to check to sqrt(n)
    for (int i=5; i*i<=n; i=i+6) 
        if (n%i == 0 || n%(i+2) == 0) 
           return false; 
  
    return true; 
}


//recursively build
vector<int> Solve(int digits)
{   
    if(digits == 1)
    {
        vector<int> v = {2,3,5,7};
        return v;
    }

    vector<int> prev = Solve(digits - 1);
    vector<int> now;

    for(int i = 0; i < prev.size(); i++)
    {
        for(int j = 1; j <= 9; j += 2)
        {
            int num = prev[i] * 10 + j;

            if(IsPrime(num)) now.push_back(num);
        }
    }
    return now;
}

int main()
{
    ifstream fin("sprime.in");
    ofstream fout("sprime.out");

    int kDigits;
    fin >> kDigits;
    fin.close();

    vector<int> super_prime_ribs = Solve(kDigits);

    for (auto v : super_prime_ribs)
        fout << v << endl;

    fout.close();
    return 0;
}
