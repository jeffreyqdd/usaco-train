/*
ID: jeffrey66
TASK: concom
LANG: C++11
*/

#include <iostream>
#include <fstream>
using namespace std;

#define MAX_COMP 101


int shares[MAX_COMP][MAX_COMP] = {},      //owns[a][b], company a owns x% of company b's stock
    controls[MAX_COMP][MAX_COMP] = {};  //controls[a][b], company a controls company b

/* recursively find controlling companies */
void updateControl(int i, int j)
{   
    //already knew this
    if(controls[i][j])
        return;

    //remember
    controls[i][j] = 1;

    //add J's ownings to I
    for(int k = 0; k < MAX_COMP; k++)
    {
        shares[i][k] += shares[j][k];
    }

    //since i now control j, controllers of i also control j

    for(int k = 0; k < MAX_COMP; k++)
    {
        if(controls[k][i] == 1)
            updateControl(k, j);
    }

    for(int k = 0; k < MAX_COMP; k++)
    {
        if(shares[i][k] > 50)
            updateControl(i,k);
    }
}

void updateShares(int i , int j, int p)
{
    //cout << "entering " <<  i << " aquires " << p << " of " << j << endl;
    //sdfsfcout << controls[1][1] << endl;
    //add to all controllers of i
    //remember that i also controls i
    for(int k = 0; k < MAX_COMP; k++)
    {
        if(controls[k][i] == 1)
        {
            //cout << i << " aquires " << p << " of " << j << endl;
            shares[k][j] += p;
        }
    }

    //check controllers
    for(int k = 0; k < MAX_COMP; k++)
    {
        if(shares[k][j] > 50)
        {
            //cout << k << " now controls " << j << endl;
            updateControl(k,j);
        }
    }

}

/*
 * Food for thought: Company a, may control company b, and be controlled by company c
 * Food for thought: Company a controls company a
 * 
 * i,j,p: update companies that control i with p% of j
 * if the controlling companies own more than 50% of j, mark the companies as controllers of j
 * 
 * when marking controlling companies, transfer all of j's ownings to company i and notify all controllers
 * of i to update their ownings to inlclude company j.
 * 
 * check if i, after absorbing j, owns more companies.
 */
int main()
{
    ifstream fin("concom.in");
    ofstream fout("concom.out");

    int kComp; fin >> kComp;

    //company i controls company i
    for(int i = 0; i < MAX_COMP; i++)
        controls[i][i] = 1;
    
    for(int a = 0; a < kComp; a++)
    {
        int i,j,p; fin >> i >> j >> p;
        updateShares(i,j,p);
    }

    for(int i = 0; i < MAX_COMP; i++)
    {
        for(int j = 0; j < MAX_COMP; j++)
        {
            if(controls[i][j] && i != j)
                fout << i << " " << j << endl;
        }
    }

    fin.close();
    fout.close();

    return 0;
}