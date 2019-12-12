/*
ID: jeffrey66
TASK: prefix
LANG: C++11
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

int main()
{
    ifstream fin("prefix.in");
    ofstream fout("prefix.out");


    vector<string> primitives;
    vector<bool> visited;
    string sequence = "";

    while (true) {
        string word; fin >> word;
        if (word == ".") break;
        primitives.push_back(word);
    }

    while (fin.good()) {
        string l;
        fin >> l;
        sequence += l;
    }

    visited.resize(sequence.length(), false);


    int result = 0;
    for(int i = 0; i <= sequence.length(); i++)
    {
        for(string& word : primitives)
        {
            int start = i - word.size();

            if(start < 0) continue;
            if(sequence.substr(start, word.size()) != word) continue;
            if(start > 0 && !visited[start]) continue;

            visited[i] = true;
            result = i;

        }
    }

    fout << result << endl;

    return 0;
}