#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

string board[3][3];

int Check(string c1, string c2, string c3)
{
    //return 0 if not possible
    //return 1 if single is possible
    //return 2 if team is possible
    if (c1 == c2 && c2 == c3)
        return 1;
    if (c1 == c2 || c1 == c3 || c2 == c3)
        return 2;
    else
        return 0;
}
string Diff(string c1, string c2, string c3)
{
    string s = "";
    if (c1 != c2)
    {
        s = c1 + c2;
    }
    if (c2 != c3)
    {
        s = c2 + c3;
    }
    else
    {
        s = c1 + c3;
    }
    sort(s.begin(), s.end());
    return s;
}
void CheckRow(set<string> &single, set<string> &team)
{
    for (int r = 0; r < 3; r++)
    {
        int outcome = Check(board[r][0], board[r][1], board[r][2]);
        if (outcome == 1)
            single.insert(board[r][0]);
        else if (outcome == 2)
            team.insert(Diff(board[r][0], board[r][1], board[r][2]));
    }
    return;
}

void CheckCol(set<string> &single, set<string> &team)
{
    for (int c = 0; c < 3; c++)
    {
        int outcome = Check(board[0][c], board[1][c], board[2][c]);
        if (outcome == 1)
            single.insert(board[0][c]);
        else if (outcome == 2)
            team.insert(Diff(board[0][c], board[1][c], board[2][c]));
    }
    return;
}

void CheckDiag(set<string> &single, set<string> &team)
{
    int outcome = Check(board[0][0], board[1][1], board[2][2]);
    if (outcome == 1)
        single.insert(board[0][0]);
    else if (outcome == 2)
        team.insert(Diff(board[0][0], board[1][1], board[2][2]));

    outcome = Check(board[0][2], board[1][1], board[2][0]);
    if (outcome == 1)
        single.insert(board[2][0]);
    else if (outcome == 2)
        team.insert(Diff(board[0][2], board[1][1], board[2][0]));

    return;
}

int main()
{
    ifstream fin("tttt.in");
    ofstream fout("tttt.out");

    set<string> single, team;

    for (int r = 0; r < 3; r++)
    {
        string s;
        fin >> s;
        for (int c = 0; c < 3; c++)
            board[r][c] = s[c];
    }

    CheckRow(single, team);
    CheckCol(single, team);
    CheckDiag(single, team);

    fout << single.size() << endl
         << team.size() << endl;

    fout.close();

    return 0;
}