#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

//#define NDEBUG

#ifdef NDEBUG
#define Debug(x)
#define DebugCollection(x)
#define DebugCollectionTill(x, l)
#else
#define Debug(x) cout << x
#define DebugCollection(x)    \
    do                        \
    {                         \
        cout << "[";          \
        for (auto e : x)      \
            cout << e << ","; \
        cout << "]" << endl;  \
    } while (0)

#define DebugCollectionTill(x, l) \
    do                            \
    {                             \
        cout << "(" << l << ")["; \
        int i_dbg = 0;            \
        for (auto e : x)          \
            if (i_dbg++ == l)     \
                break;            \
            else                  \
                cout << e << ","; \
        cout << "]" << endl;      \
    } while (0)

#endif

int kCow, kStatus, kFixed;

int NextValidPos(int &prev_visit_pos, int current_cow, int next_cow, vector<int> const &order_cp)
{
    //finds optimal position for a cow with social status
    //will return -1 if it breaks a rule

    for (int i = prev_visit_pos; i <= kCow; i++)
    {
        //iterate to next open slot while checking if any rules are violated

        if (order_cp[i] == next_cow)
        {

            //Debug("Invalid bc rule 2" << endl);
            //Debug(current_cow << ":" << next_cow << " was the input. Index i:" << i << "of order was" << order_cp[i] << endl);
            return -1;
        }

        //check if already in order and hop
        if (order_cp[i] == current_cow)
        {
            prev_visit_pos = i;
            return i;
        }

        //no rules are violated
        if (order_cp[i] == 0)
        {
            //currently in the best postion for the cow
            //if last number;
            if (next_cow == -1)
            {
                prev_visit_pos++;
                return i;
            }

            //set position to next if next is already recorded
            for (int j = i; j <= kCow; j++)
            {

                if (order_cp[j] == next_cow)
                {
                    prev_visit_pos = j;
                    return i;
                }
            }
            prev_visit_pos++;
            return i;
        }
    }
    return -1;
}

//given a hierarchal order, this function checks if it is valid (as in it satisfies the constraints)
//returns position of cow 1 or -1 if the social status order is invalid
int IsValidSocialOrder(vector<int> status_cp, vector<int> const &orig_order)
{

    vector<int> order_cp(orig_order);
    DebugCollectionTill(order_cp, kCow);

    int pos = 1;

    int candidate = 0;

    for (int i = 0; i < status_cp.size(); i++)
    {
        int current_cow = status_cp[i];
        int next_cow = -1;

        if (i < status_cp.size() - 1)
            next_cow = status_cp[i + 1];

        int index = NextValidPos(pos, current_cow, next_cow, order_cp);

        Debug(current_cow << ":" << next_cow << "-->" << index << endl);

        if (index != -1)
        {
            order_cp[index] = current_cow;
            if (current_cow == 1)
                candidate = index;
        }
        else
        {
            return -1;
        }
        DebugCollectionTill(order_cp, kCow);
        Debug(endl);
    }
    return candidate;
}

int main()
{
    ifstream fin("milkorder.in");
    ofstream fout("milkorder.out");

    vector<int> status, order(101, 0);

    //Total # of cows, cows in social status, cows in fixed positions;
    fin >> kCow >> kStatus >> kFixed;

    //read in status and check if cow 1 is present
    bool is_present = false;
    for (int i = 0; i < kStatus; i++)
    {
        int cow_num;
        fin >> cow_num;
        if (cow_num == 1)
            is_present = true;
        status.push_back(cow_num);
    }

    //fill in order with fixed cows
    for (int i = 0; i < kFixed; i++)
    {
        int id, pos;
        fin >> id >> pos;

        if (id == 1)
        {
            fout << pos << endl;
            fout.close();
            return 0;
        }
        order[pos] = id;
    }

    vector<int> status_cp(status);

    if (!is_present)
    {
        status_cp.insert(status_cp.begin(), 1);
    }

    //DebugCollectionTill(order_cp, 10);
    DebugCollection(status_cp);
    if (is_present)
    {
        fout << IsValidSocialOrder(status_cp, order) << endl;
    }
    else
    {
        int count = 0;
        while (true)
        {
            int ret = IsValidSocialOrder(status_cp, order);
            if (ret > 0)
            {
                fout << ret << endl;
                break;
            }
            else
            {
                iter_swap(status_cp.begin() + count, status_cp.begin() + count + 1);
                count++;
            }
        }
    }

    fout.close();
    return 0;
}