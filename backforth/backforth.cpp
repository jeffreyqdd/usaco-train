#include <iostream>
#include <fstream>
#include <set>
using namespace std;

int barn1[11], barn2[11];

set<int> milk_storage;

void Search(int b1[11], int b2[11],int milk, int day){
    
    int bucket;
    //cout << day << endl;
    
    for(int i=0; i<11; i++) cout << b1[i] << " ";
    cout << endl;
    for(int i=0; i<11; i++) cout << b2[i] << " ";
    cout << endl<<endl;
    

    if(day >= 5){
        milk_storage.insert(milk);
        return;
    }

    if(day%2){
        for(int i=0 ;i<11; i++){
            if (b1[i] == 0) continue;
            bucket = b1[i];
            b1[i] = 0;
            for(int j=0; j<11; j++){
                if(b2[j] == 0){
                    b2[j] = bucket;
                    Search(b1,b2,milk-bucket,day+1);
                    b2[j] = 0;
                    b1[i] = bucket;
                }
            }
            b1[i] = bucket;
        }
    }else{
        for(int i=0; i<11; i++){
            if(b2[i] == 0) continue;
            bucket = b2[i];
            b2[i] = 0;
            for(int j=0; j<11; j++){
                if(b1[j] == 0){
                    b1[j] = bucket;
                    Search(b1,b2,milk + bucket, day+1);
                    b1[j] = 0;
                    b2[i] = bucket;
                }
            }
            b2[i] = bucket;
        }
    }
    return;
}

int main(){
    ifstream fin("backforth.in");
    ofstream fout("backforth.out");
    
    for(int i=0; i<10; i++){
        fin >> barn1[i];
    }
    for(int i=0; i<10; i++){
        fin >> barn2[i];
    }

    fin.close();

    Search(barn1,barn2, 1000, 1);
    for(auto n : milk_storage) cout << n <<" ";
    cout <<endl;
    fout << milk_storage.size() << endl;

    fout.close();
}