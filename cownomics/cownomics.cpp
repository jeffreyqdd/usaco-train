#include <iostream>
#include <fstream>
#include <cmath>
#include <set>
#include <cstdlib>
using namespace std;

/*
*We cannot do brute-force string comparisons since that would yield an solution that is too slow
*Rather, we compute a rolling hash (dot product) int O(n) and compare the hashes in O(1) time.
*This approach is rather clean and efficient. 
*/

/* 
* So what's going on here?

* we read the input of spotty cows into a spotty cow array(string) and plain into an array of plain cows
* our hashes are dot products so we fill a multiplier array [0, M) with a random number % base

* start with a window of a = 0, b = 0,

* if there are duplicates --> increase window (b)
    * update the rolling hash (spotted) via current_hash + newCharVal * multiplier (for each spotted)
        * store new hash in a set
    * compute the new hashes of the plain, if set.count(newPlainHash) > 0 --> dups.
* if no duplicates --> decrease window (a)
    * why can we do this? when increasing window, whe have already visited and concluded the old values are useless
    * update the rolling hash (spotteed) via current_hash - oldCharVal * multiplier (for each spotted)
        * store new hash in set
    * compute the new hashes of the plain in the same manner, if(set.count(newPlainHash) > 0) --> dups

* best = min(best, b - a), the window has been shifted accordingly after each round. 
*/

#define BASE 1000000000

string spotty[500], plain[500];
unsigned long long spottyHash[500] = {}, plainHash[500] = {}, vectorMulti[500];

int main()
{
    ifstream fin("cownomics.in");
    ofstream fout("cownomics.out");

    int kCows, kGeneLen; fin >> kCows >> kGeneLen;

    for(int i = 0; i < kCows; i++) fin >> spotty[i];
    for(int i = 0; i < kCows; i++) fin >> plain[i];
    for(int i = 0; i < kGeneLen; i++) vectorMulti[i] = rand() % BASE;
    
    fin.close();

    //best = min gene len needed to distinguish
    //dups (duplicates) = # of cows [of the other type] that have the same gene
    //hash window (a,b);
    int best = kGeneLen, dups = kCows, a = 0, b = 0;

    while(b < kGeneLen)
    {
        if(dups == 0) best = min(best, b - a); //best window

        //increase window
        if(dups > 0)
        {
            dups = 0;
            set<int> window;

            for(int k = 0; k < kCows; k++) window.insert(spottyHash[k] += vectorMulti[b] * spotty[k][b]);
            for(int k = 0; k < kCows; k++)
                if(window.count(plainHash[k] += vectorMulti[b] * plain[k][b]) > 0)
                    dups++;
            b++;
        }
        //decrease window
        else
        {
            dups = 0;
            set<int> window;
            for(int k = 0; k < kCows; k++) window.insert(spottyHash[k] -= vectorMulti[a] * spotty[k][a]);
            for(int k = 0; k < kCows; k++)
                if(window.count(plainHash[k] -= vectorMulti[a] * plain[k][a]) > 0)
                    dups++;
            a++;
        }
    }
    
    fout << best << endl;
    fout.close();

    return 0;
}