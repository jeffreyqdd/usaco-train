/*
ID: jeffrey66
TASK: namenum
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


bool test(string name, long long n){
    string cow = "";

    for (auto c : name){
        if(c == 'A'|| c == 'B'|| c == 'C') cow = cow + "2";
        else if(c == 'D'|| c == 'E'|| c  == 'F') cow = cow + "3";
        else if(c == 'G'|| c == 'H'|| c  == 'I') cow = cow + "4";
        else if(c == 'J'|| c == 'K'|| c  == 'L') cow = cow + "5";
        else if(c == 'M'|| c == 'N'|| c  == 'O') cow = cow + "6";
        else if(c == 'P'|| c == 'R'|| c  == 'S') cow = cow + "7";
        else if(c == 'T'|| c == 'U'|| c  == 'V') cow = cow + "8";
        else cow = cow + "9";
    }
    if(to_string(n) == cow) return true;
    else return false;
}

int main(){

    ifstream fin("namenum.in");
    ifstream dict("dict.txt");
    ofstream fout("namenum.out");

    long long n;
    vector<string> names;

    fin >> n;
    fin.close();
    
    //cout << n << endl;
    
    string s;

    while(!dict.eof()){
        dict >> s;
        names.push_back(s);
    }
    //cout << "here" << endl;
    dict.close();


    int cnt = 0;

    for(auto i : names){
        //if (i == "KRISTOPHER") cout << "tested\n";
        if (test(i,n)){
            fout << i << endl;
            //cout << "written\n";
            cnt ++;
        }
    }

    if (cnt == 0) fout << "NONE\n";

    fout.close();

    return 0;
}