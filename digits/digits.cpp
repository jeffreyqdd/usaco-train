#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

int ToDecimal(string s, int base)
{
    int decimal = 0;
    int j = 0;
    for (int i = s.length() - 1; i >= 0; i--)
    {
        cout << (s[i] - '0') * pow(base, j) << endl;
        decimal += (s[i] - '0') * pow(base, j);
        j++;
    }

    return decimal;
}

int main()
{
    ifstream fin("digits.in");
    ofstream fout("digits.out");

    string n1, n2;
    fin >> n1 >> n2;

    fin.close();
    fout.close();

    cout << ToDecimal("10101010001", 2) << endl;
    return 0;
}