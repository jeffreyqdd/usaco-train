#include <iostream>
#include <fstream>

using namespace std;

//comment to start debugging
//un-comment to stop debugging
//#define NDEBUG

#ifdef NDEBUG
#define Debug(x)
#define DebugList(x, rows, columns)
#else
#define Debug(x) cout << x
#define DebugList(x, rows, columns)       \
    for (int r = 0; r < rows; r++)        \
    {                                     \
        for (int c = 0; c < columns; c++) \
        {                                 \
            cout << x[r][c] << " ";       \
        }                                 \
        cout << endl;                     \
    }
#endif

#define MAX_N 50

char puzzle[MAX_N + 1][MAX_N + 1];
int solution[2500][2], total = 0;
int kRows, kChars;

bool IsValidSpace(int r, int c, char orientation) // h=horz, v=vert
{

    //testing horizontal
    if (puzzle[r][c + 1] == '.' && puzzle[r][c + 2] == '.' && orientation == 'h')
        return true;
    //testing vertical
    if (puzzle[r + 1][c] == '.' && puzzle[r + 2][c] == '.' && orientation == 'v')
        return true;
    //else
    return false;
}
bool IsSolution(int r, int c)
{
    //if on boundary and is not black
    if (r == 0 && (puzzle[r][c] != '#'))
    {
        //test
        if (IsValidSpace(r, c, 'v'))
        {
            puzzle[r][c] = '!';
            return true;
        }
    }
    if (c == 0 && (puzzle[r][c] != '#'))
    {
        if (IsValidSpace(r, c, 'h'))
        {
            puzzle[r][c] = '!';
            return true;
        }
    }

    //if touching black squares
    if (puzzle[r - 1][c] == '#' && puzzle[r][c] != '#')
    {
        if (IsValidSpace(r, c, 'v'))
        {
            puzzle[r][c] = '!';
            return true;
        }
    }
    if (puzzle[r][c - 1] == '#' && puzzle[r][c] != '#')
    {
        if (IsValidSpace(r, c, 'h'))
        {
            puzzle[r][c] = '!';
            return true;
        }
    }

    //else
    return false;
}

void Solve()
{
    for (int r = 0; r < kRows; r++)
    {
        for (int c = 0; c < kChars; c++)
        {
            if (IsSolution(r, c))
            {
                solution[total][0] = r;
                solution[total][1] = c;
                total++;
            }
        }
    }
}

int main()
{

    // stop test zone

    ifstream fin("crosswords.in");
    ofstream fout("crosswords.out");

    fin >> kRows >> kChars;

    for (int r = 0; r < kRows; r++)
    {
        for (int c = 0; c < kChars; c++)
        {
            fin >> puzzle[r][c];
        }
    }

    //Debug(IsValidSpace(3, 1) << endl);

    DebugList(puzzle, kRows, kChars);

    Solve();
    Debug(endl);
    DebugList(puzzle, kRows, kChars);
    Debug(total << endl);
    DebugList(solution, total, 2);

    fout << total << endl;

    for (int r = 0; r < total; r++)
    {
        fout << solution[r][0] + 1 << " " << solution[r][1] + 1 << endl;
    }

    return 0;
}
