/*
ID: jeffrey66
TASK: pprime
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<int> super_prime_ribs;

bool IsPrime(int n)
{
    if (n <= 3)
        return n > 1;
    else if (n % 2 == 0 || n % 3 == 0)
        return false;

    int i = 5;

    while (i * i <= n)
    {

        if ((n % i) == 0 || (n % (i + 2)) == 0)
            return false;
        i += 6;
    }
    return true;
}

bool IsSuperPrime(int n)
{
    for (; n > 0; n /= 10)
    {
        if (!IsPrime(n))
            return false;
    }
    return true;
}

void Solve(int digits)
{
    //start with base num for ex if kDigits = 3, base num = 111
    int num = 0;
    int j = 1;
    for (int i = 0; i < digits; i++)
    {
        num += j;
        j *= 10;
    }

    cout << to_string(num).size() << endl;
    //check validity

    //probably use sieve of eratoshenes to make it go faster
    for (; to_string(num).size() == digits;)
    {
        if (IsSuperPrime(num))
            super_prime_ribs.push_back(num);

        if (digits == 1)
            num += 1;
        else
            num += 2;
    }
}

int main()
{
    ifstream fin("sprime.in");
    ofstream fout("sprime.out");

    int kDigits;
    fin >> kDigits;
    fin.close();

    Solve(kDigits);

    for (auto v : super_prime_ribs)
        fout << v << endl;

    fout.close();
    return 0;
}
