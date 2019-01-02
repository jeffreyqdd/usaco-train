#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

struct Event
{
    int day;
    int id;
    int change;

    bool operator<(const Event &e) const{
        return day < e.day;
    }
};

int kEvents, kGallons;

//table of cow id and milk production
//    return vector with new leader id;
//    return maximum milk //leader production;
void ElectNewLeaders(map<int,int> const & prod_table, set<int> &leaders, int &max_output)
{
    set<int> new_lb;
    int new_max = 0;

    for(auto row : prod_table)
    {
        if(row.second > new_max)
        {
            new_max = row.second;
            new_lb.clear();
            new_lb.insert(row.first);
        }
        else if(row.second == new_max)
        {
            new_lb.insert(row.first);
        }
    }   

    leaders = new_lb;
    max_output = new_max;

}

int Solve(vector<Event> const& event_log)
{
    //test size is extrememly large need O(N)
    map<int, int> milk_table;
    set<int> lb; //leaderboard
    int max_milk = 0;

    int update_photo_count = 0;

    for (auto coi : event_log) // coi = cow_of_interest
    {
        //update milk production of cow of interest from event
        if(milk_table.find(coi.id) != milk_table.end())
            milk_table[coi.id] += coi.change;
        else
            milk_table[coi.id] = kGallons + coi.change;

        int cow_output = milk_table[coi.id];

        //cout << coi.id << " : " << cow_output << endl;
        
        if (lb.size() == 1 && lb.find(coi.id) !=  lb.end())//coi was sole leader
        {
            //more - update leader's milk production
            if(cow_output > max_milk)
                max_milk = cow_output;
            //less - ELECT_NEW_LEADERS()
            else if (cow_output < max_milk)
            {
                set<int> lb_cp = lb;
                
                // IMPORTATNT
                lb.clear(); max_milk=0;

                ElectNewLeaders(milk_table, lb, max_milk);

                //compare lb_cp (before) with lb (after)

                //if not the same leader, update photo
                if(lb_cp != lb)
                {
                    update_photo_count++;
                } 
            }
            //equal - assert false
            /*
            else
                assert(false);
            */
        }
        //coi was in a tie
        else if (lb.size() > 1 && lb.find(coi.id) !=  lb.end() )// compare cow of interest to previous leaders: 
        {
            // more - coi becomes sole leader, update photo
            if(cow_output > max_milk)
            {
                max_milk = cow_output;
                lb.clear();
                lb.insert(coi.id);
                update_photo_count++;
            }
            // less - remove coi from leaderboard, update photo
            else if(cow_output < max_milk)
            {
                lb.erase(coi.id);
                update_photo_count++;
            }
            /*
            else{ // equal - assert false
                assert(false);
            }
            */
        }
        //coi is nothing
        else // compare cow of interest to previous leaders: 
        {
            // more -  coi becomes sole leader, update photo, update maximum milk
            if(cow_output > max_milk)
            {   
                //cout << "coi is sole leader: " << endl;
                max_milk = cow_output;
                lb.clear();
                lb.insert(coi.id);
                update_photo_count++;
            }
            // equal - coi is added to new leader list, update photo
            else if(cow_output == max_milk)
            {
                //cout << "coi ties with leader(s): " << endl;
                lb.insert(coi.id);
                update_photo_count++;
            }
            // less - ignore

        
        //take special care when the maximum milk production is either below or tied with kGallons
        }
    }
    return update_photo_count;
}

int main()
{
    ifstream fin("measurement.in");
    ofstream fout("measurement.out");

    fin >> kEvents >> kGallons;
 
    vector<Event> milk_log(kEvents);

    for (int i = 0; i < kEvents; i++)
        fin >> milk_log[i].day >>  milk_log[i].id >>  milk_log[i].change;

    sort(milk_log.begin(), milk_log.end());

    fin.close();

    fout << Solve(milk_log) << endl;

    fout.close();

    return 0;
}