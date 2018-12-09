#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

int kCows;
int shuffle_order[100], cow_order[100], copy_order[100];
map<int, int> previous; //this maps current position to previous position

void solve(vector<int> &answer){

    for(int i=0; i<3; i++){
        for(int s = 0; s<kCows; s++){
            int last = previous[s];
            copy_order[last] = cow_order[s];
            /*
            for(int i=0; i<kCows; i++){
                cout << copy_order[i] <<" ";
            }
            cout << endl;
            */
        }
        for(int i=0 ; i<kCows; i++){
            cow_order[i] = copy_order[i];
        }
    }


    for(int i = 0; i<kCows; i++){
        answer.push_back(cow_order[i]);
    }
}


int main()
{
    ifstream fin("shuffle.in");
    ofstream fout("shuffle.out");

    fin >> kCows;
    for (int i = 0; i < kCows; i++)
    {
        fin >> shuffle_order[i];
    }
    for (int i = 0; i < kCows; i++)
    {
        fin >> cow_order[i];
    }
    fin.close();

    //precalculate
    for (int i = 0; i < kCows; i++)
    {

        for (int j = 0; j < kCows; j++)
        {
            //cout << i + 1 << " <-- " << shuffle_order[j] << endl;

            if (i + 1 == shuffle_order[j])
            {
                previous[i] = j;
                break;
            }
        }
    }

    vector<int> order;
    solve(order);

    /*
    for(auto x : previous){
        cout << x.first <<":"<<x.second << endl;
    }

    for(auto x : order){
        cout << x << endl;
    }

    */

    for(auto x : order){
        fout << x << endl;
    }

    fout.close();
    return 0;
}