#include <iostream>
#include <fstream>

using namespace std;



int main(){
    ifstream fin("crazy.in");
    ofstream fout("crazy.out");

    int kFence, kCow;
    fin >> kFence >> kCow;


    fin.close();

    fout.close();

}