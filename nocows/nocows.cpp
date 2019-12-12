/*
ID: jeffrey66
TASK: nocows
LANG: C++11
*/

#include <iostream>
#include <fstream>
using namespace std;

#define MOD 9901
#define MAX_DEPTH 101
#define MAX_NODE 202


int table[MAX_DEPTH][MAX_NODE],
    smalltrees[MAX_DEPTH][MAX_NODE],
    kNodes,kDepth,c;

int main() {

    ifstream fin("nocows.in");
    ofstream fout("nocows.out");

    fin >> kNodes >> kDepth; fin.close();

    table[1][1]=1;

    for(int depth = 2; depth <= kDepth; depth++)
    {
        for(int nodes = 1; nodes <= kNodes; nodes += 2)
        {
            for(int left = 1; left <= nodes - 1 - left; left += 2)
            {
                int right = nodes - 1 - left;

                if(left != right)
                    c = 2;
                else
                    c = 1;

                table[depth][nodes] += c * 
                (
                    smalltrees[depth - 2][left] * table[depth - 1][right] + 
                    table[depth - 1][left] * smalltrees[depth - 2][right] +
                    table[depth - 1][left] * table[depth - 1][right]

                );
                
                /*cout << "checking depth: " << depth << " node: " << nodes << endl;
                cout << "   left: " << left << endl;
                cout << "   right: " << right << endl;
                cout << "   ways: " << table[depth][nodes] << endl;
                

                for(int i = 0; i < 10; i++)
                {
                    for(int j = 0; j < 10; j++)
                        cout << table[i][j] << ' ';
                    cout << endl;
                }
                cout << endl << endl;*/


                table[depth][nodes] %= MOD;
            }
        }

        for(int k = 0; k <= kNodes; k++)
        {
            smalltrees[depth - 1][k] += table[depth - 1][k] + smalltrees[depth-2][k];
            smalltrees[depth-1][k]%=MOD; 
        }
    }

    fout << table[kDepth][kNodes] << endl;
    

    return 0;
}