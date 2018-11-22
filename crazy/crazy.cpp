#include <iostream>
#include <fstream>
#include <set>
#include <vector>
using namespace std;

#define MAX_BOUND 1000000
#define MIN_BOUND 0

struct Point
{
    int x;
    int y;

    bool operator==(const Point &a) const
    {
        return x == a.x && y == a.y;
    }

    bool operator<(const Point &a) const{
        return x < a.x;
    }
    string print()
    {
        return "(" + to_string(x) + "," + to_string(y) + ")";
    }

    // my UP neighbor's coordindates
    Point up() { return {x, y + 1}; }

    Point down() { return {x, y - 1}; }

    Point left() { return {x - 1, y}; }

    Point right() { return {x + 1, y}; }
};

struct Line
{
    Point start;
    Point stop;

    bool is_horizontal()
    {
        return start.y == stop.y;
    }

    bool is_vertical()
    {
        return start.x == stop.x;
    }

    // check is a given point p in this line
    bool is_touched(Point p)
    {

        //on edge -- for both start and stop
        if (p == start || p == stop)
        {
            //cout << p.print() << endl;
            return true;
        }

        //hortizontal
        if (is_horizontal() && p.y == start.y &&
            ((p.x > start.x && p.x < stop.x) || (p.x > stop.x && p.x < start.x)))
        {
            //cout << p.print() << endl;
            return true;
        }

        //vertical
        if (is_vertical() && p.x == start.x &&
            ((p.y > start.y && p.y < stop.y) || (p.y > stop.y && p.y < start.y)))
        {
            //cout << p.print() << endl;
            return true;
        }
        return false;
    }
};

int kFence, kCow;
vector<Line> fence;
vector<Point> cow_coord;
set<Point> seen_cows;

bool is_border(Point p){
    cout<< "entering is border with" << p.print()<<":"; 

    if(p.x == MAX_BOUND || p.y == MAX_BOUND
    || p.x == MIN_BOUND || p.y == MIN_BOUND){
        cout << "hit virtual boundary\n";
        return true;
    }
    for(auto f: fence){
        if(f.is_touched(p)){
            cout << "hit fence\n";
            return true;
        }
    }
    cout << "no hit\n";
    return false;
}

bool is_cow(Point p){
    for(auto c : cow_coord){
        if(p == c){
            return true;
        }
    }
    return false;
}


void fill(Point p, int& counter, set<Point>& have_seen)
{

    cout<< "entering fill:"<<p.print()<<" counter=" <<counter<<endl;

    //find adjacent points until touch border
    cout<<"I have seen\n";

    for(auto s : have_seen){
        cout << s.print() <<" ";
    }
    cout << endl;
    

    if(have_seen.find(p) !=  have_seen.end()) {
        //cout<<"seen this before " << p.print() <<endl;
        return;
    }

    if(is_cow(p)){
        cout << "The cow:" << p.print()<<endl;
        counter++;
    }

    have_seen.insert(p);

    if(!is_border(p.up())) fill(p.up(), counter,have_seen);

    if(!is_border(p.down())) fill(p.down(), counter,have_seen);

    if(!is_border(p.left())) fill(p.left(), counter,have_seen);

    if(!is_border(p.right())) fill(p.right(), counter,have_seen);

    cout<< "exiting fill:"<<p.print()<<" counter=" <<counter<<endl;

}

int solve()
{
    int max_cow = 0;
    set<Point> seen;

    /*
    for(auto c: cow_coord){
        int counter=0;
        fill(c, counter, seen);
        max_cow = max(max_cow, counter);
    }
    */
    int counter = 0;
    fill(cow_coord[0], counter, seen);
    return max_cow;
}

int main()
{
    ifstream fin("crazy.in");
    ofstream fout("crazy.out");

    fin >> kFence >> kCow;

    for (int i = 0; i < kFence; i++)
    {
        int x1, y1, x2, y2;
        fin >> x1 >> y1 >> x2 >> y2;
        fence.push_back({{x1, y1}, {x2, y2}});
    }

    for (int i = 0; i < kCow; i++)
    {
        int x1, y1;
        fin >> x1 >> y1;
        cow_coord.push_back({x1, y1});
    }

    fin.close();

    cout << solve() << endl;
    
    fout.close();
    return 0;
}
