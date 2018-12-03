#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//no need for permutation
//just get the max of each letter from each set and add it to a letter count list

int letter_cnt[26];

int word1_cnt[26];
int word2_cnt[26];

int main()
{
    ifstream fin("blocks.in");
    ofstream fout("blocks.out");

    int kSets;
    fin >> kSets;

    for (int i = 0; i < kSets; i++)
    {
        string s1, s2, combined = "";
        fin >> s1 >> s2;

        for (auto c : s1)
        {
            word1_cnt[c - 'a']++;
        }
        for (auto c : s2)
        {
            //process bc it's unique
            word2_cnt[c - 'a']++;
        }

        for (int j = 0; j < 26; j++)
        {
            letter_cnt[j] += max(word1_cnt[j], word2_cnt[j]);
            //clear
            word1_cnt[j] = word2_cnt[j] = 0;
        }
    }

    fin.close();
    for (int i = 0; i < 26; i++)
        fout << letter_cnt[i] << endl;
    fout.close();
    return 0;
}