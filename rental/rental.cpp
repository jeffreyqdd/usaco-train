#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

//fj's cows, buy milk output, buy cows
int kCows, kStores, kFarms;

//sort high to low for vector of pairs
bool comp_pair_r(pair<int,int> const &a, pair<int,int> const &b)
{
    return a.second > b.second;
}

//sort high to low for vector of integers
bool comp_r(int a, int b)
{
    return a > b;
}


int SellMoney(int const& gallons, vector<pair<int,int>> supply)
{   
    int gallons_left = gallons;
    int revenue = 0;

    while(gallons_left != 0 && !supply.empty())
    {

        int overflow = max(0, gallons_left - supply[0].first);

        if(overflow == 0)
        {
            supply[0].first -= gallons_left;
            revenue += gallons_left * supply[0].second;
            gallons_left = overflow;
            if(supply[0].first == 0) supply.erase(supply.begin());
        }
        else
        {
            gallons_left = overflow;
            revenue += supply[0].first * supply[0].second;
            supply.erase(supply.begin());
        }
    }
    

    return revenue;
}

int RentMoney(int const & rent_num, vector<int> const & rent_pricing)
{
    int revenue = 0;    
    for(int i = 0; i < rent_num; ++i)
    {
        revenue += rent_pricing[i];
    }
    return revenue;
}
int Solve(vector<int> const &cow_out, vector<pair<int,int>> buy, vector<int> rent, int net_milk)
{
    int price = 0;
    int rented = 0;
    
    //regular cow sort for easy processing
    for(int i=0; i<kCows; i++)
    {
        //i = how many cows to rent away
        int rent_rev = RentMoney(i, rent);
        int sell_rev = SellMoney(net_milk, buy);
        int total = rent_rev + sell_rev;

        if(total > price)
            price = total;
        else
            break;

        net_milk -= cow_out[i];
    }
    
    return price;
}

int main()
{
    ifstream fin("rental.in");
    ofstream fout("rental.out");

    fin >> kCows >> kStores >> kFarms;

    vector<int> cow_output(kCows);
    vector<pair<int,int>> buy_price(kStores); //<max gallons, for _ cents per gallon>
    vector<int> rent_price(kFarms); //cents per cow
    int total_milk = 0;

    for(auto &c : cow_output)
    {
        fin >> c;
        total_milk += c;
    }
    for(auto &bp : buy_price)
        fin >> bp.first >> bp.second;
    
    for(auto &rp : rent_price)
        fin >> rp;


    //cow milk production is sorted from low to high
    sort(cow_output.begin(), cow_output.end());
    //reverse sort to targest highest prices first
    sort(buy_price.begin(), buy_price.end(), comp_pair_r);
    sort(rent_price.begin(), rent_price.end(), comp_r);
    //cout << MilkMoney(27, buy_price) << endl;
    fout << Solve(cow_output, buy_price, rent_price, total_milk) << endl;
    fout.close();

    return 0;
}