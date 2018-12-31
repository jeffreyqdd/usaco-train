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
int status[101], order[101];

int NextValidPos(int &prev_visit_pos, int current_cow, int next_cow, int order_cp[101])
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
            //current_cowly in the best postion for the cow
            //if last number;
            if (next_cow == -1)
            {
                prev_visit_pos++;
                return i;
            }

            //set position to next if next is already recorded
            for (int j = i; j <= kCow; j++)
            {
                if (next_cow == 53)
                    cout << order_cp[j] << endl;

                if (order_cp[j] == next_cow)
                {
                    cout << "here\n";
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

int IsValidSocialOrder(int order_cp[101])
{
    //given a hierarchal order, this function checks if it is valid (as in it satisfies the constraints)
    //returns position of cow 1 or -1 if the social status order is invalid
    int pos = 1;

    int candidate = 0;

    for (int i = 0; i < kStatus; i++)
    {
        int current_cow = status[i], next = status[i + 1];

        int index = NextValidPos(pos, current_cow, next, order_cp);

        Debug(current_cow << ":" << next << "-->" << index << endl);

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
        for (int i = 0; i < kCow; i++)
        {
            cout << order_cp[i] << " ";
        }
        cout << endl
             << endl;
        //DebugCollectionTill(*order_cp, kCow);
    }
    return candidate;
}

int main()
{
    ifstream fin("milkorder.in");
    ofstream fout("milkorder.out");

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
        status[i] = cow_num;
    }
    if (!is_present)
    {
        status[kStatus] = 1;
        kStatus++;
    }
    status[kStatus] = -1;

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

    DebugCollectionTill(status, kStatus);
    DebugCollectionTill(order, kFixed);
    Debug(is_present << endl
                     << endl);

    //cout << IsValidSocialOrder(order) << endl;

    int order_cp[101];

    //DebugCollectionTill(order_cp, 10);

    if (is_present)
    {
        fout << IsValidSocialOrder(order) << endl;
    }
    else
    {
        int best = 200, index = 200;
        for (int i = kStatus - 1; i >= 1; i--)
        {
            DebugCollectionTill(status, kStatus);

            memcpy(order_cp, order, sizeof(order));
            index = IsValidSocialOrder(order_cp);
            if (index != -1)
                best = min(best, index);

            swap(status[i - 1], status[i]);
            //Debug(endl);
        }
        DebugCollectionTill(status, kStatus);

        memcpy(order_cp, order, sizeof(order));
        index = IsValidSocialOrder(order_cp);
        if (index != -1)
            best = min(best, index);

        fout << best << endl;
    }
    fout.close();
    return 0;
}