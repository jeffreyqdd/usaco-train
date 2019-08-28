/*
ID: jeffrey66
TASK: hamming
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

//int to binary string
string convert(int n)
{
    int binary[64];
    //cout << n;
    int i = 0;
    while(n > 0)
    {
        binary[i] = n % 2;
        n = n / 2;

        i++;
    }

    string s = "";
    for(int j = i - 1; j >= 0; j--)
        s += to_string(binary[j]);

    return s;
}

int hamming_distance(int num1, int num2)
{
    string a = convert(num1), b = convert(num2);
    //add zeros to front
    while(a.length() > b.length())
        b = "0" + b;
    while(b.length() > a.length())
        a = "0" + a;
    int cnt = 0;
    //cout << a << endl << b << endl;
    for(int i = 0; i < a.length(); i++)
        if(a[i] != b[i]) //check different
            cnt++;
    return cnt;
}

int main()
{
    ifstream fin("hamming.in");
    ofstream fout("hamming.out");

    int kCodeWords, kBitLen, kHammingDist;
    fin >> kCodeWords >> kBitLen >> kHammingDist;
    fin.close();

    int maxNum = pow(2,kBitLen);

    vector<int> valid;
    for(int i =0; i < maxNum; i++)
    {   
        bool willAdd = true;

        for(auto u : valid)
            if(hamming_distance(u,i) < kHammingDist)
                willAdd = false;

        if(willAdd)
            valid.push_back(i);
        if(valid.size() >= kCodeWords)
            break;
    }
    
    //write
    for(int i = 0; i < valid.size(); i++)
        fout << valid[i] << ((((i % 10) % 9 == 0 && i%10 != 0) || i == valid.size()- 1)? "\n": " ");
    fout.close();
    return 0;
}