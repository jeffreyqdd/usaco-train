/*
ID: jeffrey66
TASK: lamps
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

//toggle all
void button1(vector<bool>& b)
{
    for(int i = 0; i < b.size(); i++) b[i] = !b[i];
}
//toggle odd
void button2(vector<bool>& b)
{
    for(int i = 0; i < b.size(); i+=2) b[i] = !b[i];
}

//toggle even
void button3(vector<bool>& b)
{
    for(int i = 1; i < b.size(); i+=2) b[i] = !b[i];
}

//toggle every third
void button4(vector<bool>& b)
{
    for(int i = 0; i < b.size(); i+=3) b[i] = !b[i];
}

bool comp(const vector<bool>& a, const vector<bool>& b)
{
    int i;
    for(i = 0; i < a.size(); i++)
    {
        if(a[i] < b[i]) return true;
        if(a[i] > b[i]) return false;
        
    }
    return false;
}

//press same button twice undoes.
//so just check each button pressed or not.
int main()
{
    ifstream fin("lamps.in");
    ofstream fout("lamps.out");

    int kLamps, kPress;
    vector<int> lampOn, lampOff;

    fin >> kLamps >> kPress;

    for(int i = 0; ; i++)
    {
        int next; fin >> next;
        if(next == -1) break;
        lampOn.push_back(next - 1);
    }

    for(int i = 0; ; i++)
    {
        int next; fin >> next;
        if(next == -1) break;
        lampOff.push_back(next - 1);
    }

    fin.close();

    vector<bool> lamps(kLamps, true);
    vector<vector<bool>> stored;
    

    for(int a = 0; a <= 1; a++)
    {
        for(int b = 0; b <= 1; b++)
        {
            for(int c = 0; c <= 1; c++)
            {
                for(int d = 0; d <= 1; d++)
                {
                    for(int i = 0; i < lamps.size(); i++) lamps[i] = true;
                    if(a == 1) button1(lamps);
                    if(b == 1) button2(lamps);
                    if(c == 1) button3(lamps);
                    if(d == 1) button4(lamps);
                    
                    //check over press or not possible convo.
                    int flag = 0;
                    if(a + b + c + d > kPress || (kPress - a - b - c - d) % 2 == 1)
                        flag = 1;
                    
                    //check if off is off
                    for(int n : lampOff)
                        if(lamps[n] == 1) flag = 1;
                    
                    //check if on is on
                    for(int n : lampOn)
                        if(lamps[n] == 0) flag = 1;

                    if(flag == 1)  continue;

                    //literally just store it.
                    stored.push_back(lamps);

                }
            }
        }
    }

    sort(stored.begin(), stored.end(), comp);


    if(stored.size() == 0)
        fout << "IMPOSSIBLE" << endl;
    else
    {
        for(auto o : stored)
        {
            for(auto i : o)
            {
                fout << i;
            }
            fout << endl;
        }
    }

    fout.close();

}
