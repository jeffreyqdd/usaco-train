#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//comment to start debugging
//un-comment to stop debugging
#define NDEBUG

#ifdef NDEBUG
#define Debug(x)
#else
#define Debug(x) cout << x
#endif

struct Data
{
    int weight;
    bool spots; //true == Spots, false == No spots

    bool operator<(const Data &a) const
    {
        return weight < a.weight;
    }
};

int kCows, A, B; //# of cows farmer john has 'trained' his AI on, and arriving cows with integer weights [A,B]
vector<Data> training_data;
bool IsSpots(int w, int &i)
{
    for (; i <= kCows; i++)
    {
        //first we want to find the first cow of farmer john's data that surpasses weight w.
        if (training_data[i].weight > w)
        {
            //this means that the previous cow in the data set is either less than or equal to weight w.
            Data cow1 = training_data[i - 1];
            Data cow2 = training_data[i];

            Debug(cow1.weight << " - " << w << " - " << cow2.weight << "-->");

            if (w - cow1.weight == cow2.weight - w)
            {
                return cow1.spots || cow2.spots;
            }
            else if (w - cow1.weight < cow2.weight - w)
            {
                return cow1.spots;
            }
            else
            {
                return cow2.spots;
            }
        }

        //possibility weight is greater than the last cow
        if (i == kCows - 1)
        {
            Debug("testing cow weight is greater or equal than data:" << w << ">=" << training_data[i].weight << "-->");
            return training_data[i].weight;
        }
    }
    return false;
}
int Solve()
{
    int total = 0;
    int i = 0;

    for (int w = A; w <= B; w++)
    {
        //since [A,B] is in ascending order and vector training_data is sorted in ascending order, we can just iterate N times and
        //the search function will be relatively simple and does not require another N iterations.

        if (IsSpots(w, i))
        {
            Debug("true");
            total++;
        }
        Debug(endl);
    }
    return total;
}
int main()
{
    ifstream fin("learning.in");
    ofstream fout("learning.out");

    fin >> kCows >> A >> B;

    for (int i = 0; i < kCows; i++)
    {
        string s;
        bool spots = false;
        int weight;
        fin >> s >> weight;

        if (s == "S")
            spots = true;

        training_data.push_back({weight, spots});
    }

    sort(training_data.begin(), training_data.end());

    fin.close();
    fout << Solve() << endl;
    fout.close();

    return 0;
}
