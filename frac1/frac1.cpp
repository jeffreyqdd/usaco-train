/*
ID: jeffrey66
TASK: castle
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <set>
using namespace std;


struct Frac
{
    int n; //numerator
    int d; //denominator

    bool operator==(const Frac& f) const //overload == operator
    {
        if(static_cast<double>(n) / static_cast<double>(d) == static_cast<double>(f.n) / static_cast<double>(f.d))
            return true;
        return false;
    }

    bool operator<(const Frac& f) const //overload comparison operator for set sorting.
    {
        return static_cast<double>(n) / static_cast<double>(d) < static_cast<double>(f.n) / static_cast<double>(f.d);
    }
};

//euclids algorithm, finds greatest common denominator
int gcd(int a, int b)
{

    if(b == 0) return a;
    else return gcd(b, a % b);
}

void simplify(Frac &f)
{
    int g = gcd(f.n, f.d);

    f.n /= g;
    f.d /= g;
}


int main()
{
    ifstream fin("frac1.in");
    ofstream fout("frac1.out");

    int kFrac; fin >> kFrac; fin.close();

    //brutal force it..not too complex since N is relatively small
    //[1,160]
    set<Frac> calc; //store results 
    for(int n = 0; n <= kFrac; n++)
    {
        for(int d = kFrac; d >= 1; d--) //d can never be 0
        {
            if(n > d) continue;
            Frac f = {n,d};
            simplify(f);
            calc.insert(f);
        }
    }

    for(auto u : calc)
        fout << u.n << '/' << u.d << endl;

    fout.close();

}