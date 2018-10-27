/*
ID: jeffrey66
TASK: palsquare
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

string getChar(int n){
    if (n == 0) return "0";
    else if(n == 1) return "1";
    else if (n == 2) return "2";
    else if (n == 3) return "3";
    else if (n == 4) return "4";
    else if (n == 5) return "5";
    else if (n == 6) return "6";
    else if (n == 7) return "7";
    else if (n == 8) return "8";
    else if (n == 9) return "9";
    else if (n == 10) return "A";
    else if (n == 11) return "B";
    else if (n == 12) return "C";
    else if (n == 13) return "D";
    else if (n == 14) return "E";
    else if (n == 15) return "F";
    else if (n == 16) return "G";
    else if (n == 17) return "H";
    else if (n == 18) return "I";
    else return "J";
}

string convert(int n, int base){
    if(n < base) return getChar(n);
    else return convert(n / base, base) + getChar(n % base);
}

string reverseStr(string str) { 
    int n = str.length(); 

    for (int i = 0; i < n / 2; i++) 
        swap(str[i], str[n - i - 1]); 

    return str;
} 

int main(){

    ifstream fin("palsquare.in");
    ofstream fout("palsquare.out");

    //base
    int base;

    fin >> base;


    for (int n = 1; n <= 300; n++){
        string answer = convert(n*n, base);


        string rAnswer = reverseStr(answer);

        if(answer == rAnswer){
            //cout << answer << " " << rAnswer << endl;
            fout << convert(n,base) <<" "<<answer <<endl; 
        }
    }
    
    fin.close();
    fout.close();
    
    return 0;
}