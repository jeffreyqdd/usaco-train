#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <map>
using namespace std;

typedef long long intl;


//pos:slope
map<int,int> slope_change;

//Solve outputs the optimal distance
//input max_dist is the unchanged sum of the drive distances
intl Solve(intl const &max_dist)
{
    intl optimal = max_dist;

    intl slope = 0;
    intl delta_step = 0;
    intl delta_y = 0;
    intl previous_y = 0;

    int index = 0;  
    //for change : slope_change;
    for(auto change : slope_change)
    {
        //get delta position of y
        if(index == 0)
        {
            delta_y = 0;
            previous_y = change.first;
        }
        else
        {
            delta_y = change.first - previous_y;
            previous_y = change.first;
        }
        
        //update change in steps:  delta_step += curent_slope * delta position y;
        delta_step += slope * delta_y;

        //cout << change.first << ": " << slope << " * " << "" <<delta_y
             //<< " = " << delta_step << "    ---->    "; 

        //get minumum steps fj required to drive.
        optimal = min(optimal, max_dist + delta_step);
        //cout << optimal << endl;


        //update current slope by delta slope
        slope += change.second;

        index ++;   
    }

    return optimal;
}

int main()
{
    ifstream fin("teleport.in");
    ofstream fout("teleport.out");

    int kPiles; fin >> kPiles;

    intl driving_distance = 0;

    //general shape of graph is similar to absolute values
    //slope will remain same until updated
    //there are 3 point of interests, start of decrease, vertex, end of increase

    //for every pile of manure that needs to be moved
    for(int i = 0; i < kPiles; i++)
    {
        int a, b; fin >> a >> b;
        int distance = abs(a-b); //drive distance

        driving_distance += distance; 
    
        //if distance to telelport is greater or equal than drive distancex
        if(abs(a) >= distance)
            //don't take teleleport
            continue;

        //if teleporting is more efficient, there are two main cases
        slope_change[b] += 2;
        //case 1: 0 is between a and b
        //a --- 0 --- b
        //b --- 0 --- a

        if((a <= 0 && a < b) || (a >= 0 && a > b) )
        {
            slope_change[0] --;
            slope_change[2 * b]--;
        }
        //case 2: 0 is not between a and b
        // 0a----b
        //b---0a
        if((a < b && a >= 0) || (a > b && a <= 0))
        {
            slope_change[2 * a]--;
            slope_change[(2 * b) - (2 * a)]--;
        }
    }
    fout << Solve(driving_distance) << endl;

    return 0;
}