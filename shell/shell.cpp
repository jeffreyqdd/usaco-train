#include <iostream>
#include <fstream>
#include <map>
using namespace std;


int shell_pos[3] = {1,2,3};



int main()
{
    ifstream fin("shell.in");
    ofstream fout("shell.out");

    int kShuffle;
    fin >> kShuffle;

    // pebble chosen : # of times bessie chose the pebble before.
    map<int,int> score_cnt;
    int highest = 0;
    for(int i = 0; i < kShuffle; i++)
    {
        int a, b, guess;
        fin >> a >> b >> guess;
        //shuffle
        swap(shell_pos[a-1], shell_pos[b-1]);

        //guess
        
        if(score_cnt.find(shell_pos[guess-1]) != score_cnt.end())
        {
            score_cnt[shell_pos[guess-1]] += 1;
        }
        else
        {
            score_cnt[shell_pos[guess-1]] = 1;
        }
        
        highest = max(score_cnt[shell_pos[guess-1]], highest);
        
    }

    fout << highest << endl;

    fin.close();
    fout.close();

    return 0;
}