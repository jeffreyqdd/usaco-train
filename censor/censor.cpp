#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define A 107
#define B 1000007
/*
rolling hash
*/
typedef unsigned long long ull;

void solve(const vector<ull>& magazineHsh,
           const vector<ull>& correction/*,
           const vector<ull>& censorHash*/)
{
    int gap = 2;

    for(int a = 0, b = 2; b < magazineHsh.size(); a++,b++)
    {
        int subHsh = ((a == 0) ?
        magazineHsh[b] : 
        (magazineHsh[b] - magazineHsh[a - 1] * correction[b-a+1]) % B);
        cout << subHsh << endl;
    }
}

int main()
{
    ifstream fin("censor.in");
    ofstream fout("censor.out");

    string phrase; int n; fin >> phrase >> n;
    vector<string> words(n);

    for(auto &o : words)
        fin >> o;
    fin.close();
    
    //hash the magazine
    vector<ull> magazineHsh(phrase.length());
    vector<ull> p(phrase.length());

    magazineHsh[0] = phrase[0];
    p[0] = 1;
    for(int i = 1; i < phrase.length(); i++)
    {
        magazineHsh[i] = ((magazineHsh[i - 1] * A + phrase[i]) % B);
        p[i] = (p[i - 1] * A) % B;
    }

    solve(magazineHsh, p);
    

}