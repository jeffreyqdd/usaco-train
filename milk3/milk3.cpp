/*
ID: jeffrey66
TASK: milk3
LANG: C++11
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

struct Bucket
{
    int capacity;
    int milk;
};

struct State
{
    Bucket a;
    Bucket b;
    Bucket c;
};

vector<State> repeat;
set<int> c_amount;

void Pour(Bucket &a, Bucket &b) // pours from bucket a to bucket b;
{
    int overflow = max(b.capacity, b.milk + a.milk) - b.capacity;
    b.milk = b.milk + a. milk - overflow;
    a.milk = overflow;
}

bool IsSame(State s){
    for(auto r : repeat)
    {
        if(r.a.milk == s.a.milk && r.b.milk == s.b.milk && r.c.milk == s.c.milk)
        {
            repeat.push_back(s);
            return true;
        }
    }
    repeat.push_back(s);
    return false;
}

void Solve(Bucket a, Bucket b, Bucket c)
{
    //cout << a.milk<<"-" << b.milk<< "-" << c.milk << " : "<<endl;

    //base cases
    if(a.milk == 0)
    {
        c_amount.insert(c.milk);
        //cout << "a empty\n";
        
    }
    
    if(IsSame({a,b,c}))
    {
        //cout << "repeat exit\n";
        return;
    }
    

    //search, put back, search next...
    Bucket copy_a = a, copy_b = b, copy_c = c;

    
    //a to b
    //cout << "pour a to b\n";
    Pour(a,b);
    Solve(a,b,c);
    a = copy_a;
    b = copy_b;
    

    //b to a
    //cout << "pour b to a\n";
    Pour(b,a);
    Solve(a,b,c);
    a = copy_a;
    b = copy_b;
    
    
    //a to c
    //cout << "pour a to c\n";
    Pour(a,c);
    Solve(a,b,c);
    a = copy_a;
    c = copy_c;
    

    //c to a
    //cout << "pour a to c\n";
    Pour(c,a);
    Solve(a,b,c);
    a = copy_a;
    c = copy_c;

    //b to c
    //cout << "pour a to c\n";
    Pour(b,c);
    Solve(a,b,c);
    b = copy_b;
    c = copy_c;

    //c to b
    //cout << "pour a to c\n";
    Pour(c,b);
    Solve(a,b,c);
    b = copy_b;
    c = copy_c;

    //cout << "exit\n";
    return;
    
}
int main()
{
    ifstream fin("milk3.in");
    ofstream fout("milk3.out");

    Bucket a,b,c;
    fin >> a.capacity >> b.capacity >> c.capacity;
    a.milk = 0;
    b.milk = 0;
    c.milk = c.capacity;
    fin.close();

    /*
    State state = {a,b,c};
    Bucket test1= {6,5}, test2 = {3,0};
    cout << test1.milk << "   "<<test2.milk << endl;
    Pour(test1, test2);
    cout << test1.milk << "   "<<test2.milk << endl;
    cout << state.a.milk << "-"<< state.b.milk << "-"<< state.c.milk << "-"<<endl;
    */

    Solve(a,b,c);

    //cout << c_amount.size()<<endl;
    vector<int> answer;
    for(auto n : c_amount) answer.push_back(n);
    for(int i=0; i<answer.size(); i++){
        fout << answer[i];
        if(i < answer.size() - 1) fout <<" ";
    }
    fout << endl;
    fout.close();

    return 0;
}