#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <limits>
#include <algorithm>
using namespace std;

#define INF 922337203685775807ll

long long GLOBAL_MIN = INF, GLOBAL_MAX = 0;

struct Int
{
    long long value;
    long long index;

    bool operator<(const Int &i) const{
        return value < i.value;
    }
};

struct Pair
{
    long long a, b, c;

    Pair(long long num1, long long num2, long long num3)
    {
        vector<long long> temp = {num1, num2, num3};
        sort(temp.begin(), temp.end());

        a = temp[0]; b = temp[1]; c = temp[2];

        GLOBAL_MIN = min(GLOBAL_MIN, a);
        GLOBAL_MAX = max(GLOBAL_MAX, c);
        

        //cout << a << " " << b << " " << c << endl;
    }

    bool operator<(const Pair& p) const
    {
        if(a != p.a && c == p.c)
        {
            return a < p.a;
        }
        else if(a == p.a && c != p.c)
        {
            return c < p.c;
        }
        else
        {
            return c < p.c;
        }
        

        
    }
};


set<Pair> findTriplets(vector<Int> arr) 
{ 
    set<Pair> ret;
  
    // sort array elements 
    sort(arr.begin(), arr.end()); 
    



    for(long long i = 0; i < arr.size(); i++)
    {
        long long fixed = i;
        long long lb = (fixed == 0)? 1 : 0;
        long long ub = (fixed == arr.size() - 1)? arr.size()-2: arr.size()-1;


        while(lb < ub)
        {
            long long sum = arr[fixed].value + arr[lb].value + arr[ub].value;
            
            if(sum == 0 && i != lb && i != ub && lb != ub)
            {
                ret.insert(Pair(arr[fixed].index, arr[lb].index, arr[ub].index));

                if(arr[lb + 1].value == arr[lb].value)
                    lb++;
                else if(arr[ub - 1].value == arr[ub].value)
                    ub--;
                else
                {
                    lb++;
                    ub--;
                }
                
            }
            if(sum < 0)
                lb++;
            else
                ub--;
            
        }
    }
    
    return ret;
     
}

vector<long long> getRunningSum(set<Pair> p)
{
    vector<long long> running(GLOBAL_MAX + 1, 0);

    for(Pair item : p)
    {
        for(int i = item.c; i <= GLOBAL_MAX; i++)
            running[i] += 1;

        //for(int i = 1; i <= GLOBAL_MAX; i++)
            //cout << running[i] << " ";
        //cout << endl;
    }

    return running;
}
int main()
{
    ifstream fin("threesum.in");
    ofstream fout("threesum.out");

    long long N, Q;
    fin >> N >> Q;

    vector<Int> arr(N);
    
    for(long long i = 0; i < N; i++)
    {
        fin >> arr[i].value;
        arr[i].index = i + 1;
    }
    
    set<Pair> p = findTriplets(arr);
    
    for(auto o  : p)
        cout << o.a << " " << o.b << " " << o.c << endl;
    
    vector<long long> runningSum = getRunningSum(p);

    //for(int i = 1; i < runningSum.size(); i++)
        //cout<< runningSum[i] << endl;

    for(int i = 0; i < Q; i++)
    {
        int a, b; fin >> a >> b;
        cout << runningSum[b] - runningSum[a] << endl;
    }

    return 0;
}