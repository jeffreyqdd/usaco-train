#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


int main()
{
    ifstream fin("homework.in");
    ofstream fout("homework.out");

    int N; fin >> N;
    int scores[N], least[N], running = 0;

    //read
    for(int i = 0; i < N; i++)
    {
        fin >> scores[i];
        running += scores[i];
    }

    //construct least [i, last]
    for(int i = N -1, minScore = 100100; i >= 0; i--)
    {
        minScore = min(minScore, scores[i]);
        least[i] = minScore;
    }

    //running sum time
    double maxScore = 0.0;
    vector<int> answers;

    //eats at least 1st question, so start on question 2
    for(int i = 0; i < N - 2; i++)
    {
        
        running -= scores[i];
        int lowestRemoved = running - least[i];
        int numbersLeft = N - i - 1 - 1;
        
        double newMaxScore = (double) lowestRemoved / (double) numbersLeft;
        
        if(newMaxScore > maxScore)
        {
            maxScore = newMaxScore;
            answers.clear();
            answers.push_back(i + 1);
        }
        else if(newMaxScore == maxScore)
        {
            answers.push_back(i + 1);
        }


        //cout <<  "eating " << i <<" -> "<<running << " -> " << lowestRemoved << "->" << numbersLeft<< endl;;
       
        
    }

    sort(answers.begin(), answers.end());

    for(auto o : answers) fout << o << endl;

    return 0;
}
