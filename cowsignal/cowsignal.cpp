#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int kRows, kChars, kMultiply;

int main()
{
    ifstream fin("cowsignal.in");
    ofstream fout("cowsignal.out");

    fin >> kRows >> kChars >> kMultiply;

    vector<char> row;
    vector<vector<char>> cow_signal;

    //read and solve at same time
    for (int r = 0; r < kRows; r++)
    {
        for (int c = 0; c < kChars; c++)
        {
            char character;
            fin >> character;

            //push back to row k times
            for (int k = 0; k < kMultiply; k++)
            {
                row.push_back(character);
            }
        }
        //push back to cow signal k times
        for (int k = 0; k < kMultiply; k++)
        {
            cow_signal.push_back(row);
        }
        row.clear();
    }

    fin.close();

    //write

    for (auto r : cow_signal)
    {
        for (auto c : r)
            fout << c;
        fout << endl;
    }
    fout.close();
    return 0;
}