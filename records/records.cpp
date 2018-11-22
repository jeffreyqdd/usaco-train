#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
using namespace std;
/*
map containing all cow combinations with # of occurences
*/
bool is_debug = false;

int main(){

    ifstream fin("records.in");
    ofstream fout("records.out");

    int kHours; fin >> kHours;

    map<string,int> cow;
    string joined;
    vector<string> milking;
    int max_occur = 0;

    for(int i=0; i<kHours; i++){
        
        string n1,n2,n3; fin >> n1 >> n2 >> n3;
        
        milking.push_back(n1); milking.push_back(n2); milking.push_back(n3);

        sort(milking.begin(), milking.end());
        
        joined = "";
        for(auto s: milking){
            joined = joined + s;
        }

        if (is_debug) cout << joined << endl;

        if(cow.count(joined)){
            //exists
            cow[joined] += 1;
        }else{
            //no exists
            cow[joined] = 1;
        }
        max_occur = max(max_occur, cow[joined]);

        milking.clear();
    }

    fin.close();

    fout << max_occur << endl;
    
    
    return 0;
}