#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

/*
iterate starting from N-2 to 1
update lowest number and cumulative score

remaining questions = kQuestions - eaten
avg = (cumlative score - lowest number) / (remaining questions - 1)
**take care to use doubles as they offer decimal precision

condition table:
avg > highest avg
-reset output and push back questions eaten

avg = highest avg;
-another valid solution so push_back questions eaten

avg < highest avg;
-not valid solutions so ignore

---------------
O(n) should be fast enough with 3 <= N <= 100,000
*/

int kQuestions, scoring[100000];

//keep the use of doubles localized
void PrecisionAverage(double &avg, int const &cumulative, int const &lowest, int const &remaining)
{
    double d_cumulative = cumulative, d_lowest = lowest, d_remaining = remaining;

    avg = (d_cumulative - d_lowest) / d_remaining;

    return;
}

void Solve(vector<int> &solutions)
{
    // 1 <= questions_eaten <= kQuestions - 2

    int lowest_score = scoring[kQuestions - 1];

    int cumulative_score = scoring[kQuestions - 1];
    int remaining_questions;

    double highest_average = 0, average = 0;

    for (int i = kQuestions - 2; i >= 1; i--)
    {
        lowest_score = min(lowest_score, scoring[i]);
        cumulative_score += scoring[i];
        remaining_questions = kQuestions - i;

        PrecisionAverage(average, cumulative_score, lowest_score, remaining_questions - 1);

        if (average > highest_average)
        {
            solutions.clear();
            solutions.push_back(i);
            highest_average = average;
        }
        else if (average == highest_average)
        {
            solutions.push_back(i);
        }
        /*
        cout << cumulative_score << "-" << lowest_score << " / " << remaining_questions - 1
             << " = " << average << "   " << solutions.size() << "-->" << i << endl;
        */
        //else its not a solution so do nothing
    }
    return;
}

int main()
{
    ifstream fin("homework.in");
    ofstream fout("homework.out");

    fin >> kQuestions;
    for (int i = 0; i < kQuestions; i++)
        fin >> scoring[i];

    fin.close();
    vector<int> solutions;
    Solve(solutions);

    //solutions is reversed since we iterated from N-2 --> 1
    reverse(solutions.begin(), solutions.end());

    for (auto s : solutions)
        fout << s << endl;

    fout.close();

    return 0;
}
