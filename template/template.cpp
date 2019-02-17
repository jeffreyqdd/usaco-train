/*
ID: jeffrey66
TASK: beads
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <iterator>

using namespace std;

// Comment to enable debug
#define NDEBUG

#ifdef NDEBUG
#define Debug(x)
#define DebugCollection(x)
#define Debug2DCollection(x)
#define DebugCollectionTill(x, l)
#else
#define Debug(x) cout << x
#define DebugCollection(x)    \
    do                        \
    {                         \
        cout << "[";          \
        for (auto e : x)      \
            cout << e << ","; \
        cout << "]" << endl;  \
    } while (0)

#define Debug2DCollection(x)    \
    do                          \
    {                           \
        cout << "[";            \
        for (auto r : x)        \
            DebugCollection(r); \
        cout << "]" << endl;    \
    } while (0)

#define DebugCollectionTill(x, l) \
    do                            \
    {                             \
        cout << "(" << l << ")["; \
        int i_dbg = 0;            \
        for (auto e : x)          \
            if (i_dbg++ == l)     \
                break;            \
            else                  \
                cout << e << ","; \
        cout << "]" << endl;      \
    } while (0)
#endif

/*

random_input_range = [ (low,low_inclusive,high,high_inclusive), (low, high)]

random_input (ri) * IsValidInputVector (filter) = input_vector

input_vecotr (iv) * FindResult = output_vector (ov)

E.g.
iv = [a1, b1, c1, d1, e1]
ov = [r1, r2] // many cases, only one element

E.g.
input_matrix = 
[ 
    iv1,
    iv2,
    iv3
] 

output_matrix =
[ 
    ov1,
    ov2,
    ov3
 ] 
 */

/*
 * requirements for test case generator:

 */

struct GeneratorParameters
{
    GeneratorParameters() : num_of_cases(10), max_numer_of_input_tries(999999), max_number_of_output_tries(999) {}
    vector<pair<int, int>> input_vector_value_range;
    vector<pair<int, int>> output_vector_value_range;
    int num_of_cases;
    bool new_dataset_every_rune;
    int max_numer_of_input_tries;
    int max_number_of_output_tries;
};

// Tools for vector manipulation
vector<vector<int>> SplitVector(vector<int> const &iv, int num_per_segment)
{
    assert(iv.size() % num_per_segment == 0); // must be even number to do this split
    vector<vector<int>> r;
    for (int i = 0; i < iv.size(); i += num_per_segment)
    {
        vector<int> seg;
        for (int j = 0; j < num_per_segment; j++)
            seg.push_back(iv[i + j]);
        r.push_back(seg);
    }
    return r;
}

vector<int> GenVectorPerValueRange(vector<pair<int, int>> const &input_range)
{
    vector<int> iv;
    for (auto r : input_range)
        iv.push_back(rand() % (r.second - r.first) + r.first);

    return iv;
}

// TODO
bool IsValidInputVector(vector<int> iv)
{
    
    vector<vector<int>> splitted = SplitVector(iv, 2);
    set<pair<int,int>> seen;
    for(auto s : splitted)
        seen.insert({s[0],s[1]});

    if(seen.size() == iv.size()/2)
        return true;
    else
        return false;
}

// TODO
// to test whether an result is expected
//

///// Test whether p1 is over-shadowed by p2.
bool IsHiddenByAnother(vector<int> p1, vector<int> p2)
{
    int x1 = p1[0];
    int y1 = p1[1];
    int x2 = p2[0];
    int y2 = p2[1];

    if (y2 > y1) // p1 is higher
    {
        return abs(x2 - x1) <= (y2 - y1);
    }
    return false;
}

bool IsValidOutputVector(vector<int> const &iv, vector<int> const &ov)
{
    // need to check all the constraint
    // in the peak finding example: input is all peak coord, output is # of peaks can be seen
    // so how to validate the result is right without to find the actual how-to anser the problem?
    // Answer: run through all known constraints
    //
    vector<vector<int>> peaks = SplitVector(iv, 2);
    int num_of_seen = ov[0];
    int total_peaks = peaks.size();

    Debug2DCollection(peaks);

    vector<bool> hidden_by_another(total_peaks, false);

    //

    // N^(N-1), compare every peak with the rest, flag it to true if it's hidden_by_another
    for (int i = 0; i < peaks.size(); i++)
    {
        for (int j = 0; j < peaks.size(); j++)
        {
            if (j == i)
                continue; // don't compare with itself;

            if (IsHiddenByAnother(peaks[i], peaks[j]))
            {
                hidden_by_another[i] = true;
                continue;
            }
        }
    }

    int actual_can_be_seen = 0;

    for (auto h : hidden_by_another)
    {
        if (!h)
            actual_can_be_seen++;
    }

    cout << "actual can be seen =" << actual_can_be_seen << " expected=" << num_of_seen << endl;

    return actual_can_be_seen == num_of_seen;
}

vector<int> FindResult(vector<int> iv, GeneratorParameters const &para)
{
    int cnt_tries = 0;
    vector<int> output_vector;
    while (cnt_tries < para.max_number_of_output_tries)
    {
        cnt_tries++;

        auto candidate_ov = GenVectorPerValueRange(para.output_vector_value_range);
        Debug("Candidate_OV ");
        DebugCollection(candidate_ov);
        if (IsValidOutputVector(iv, candidate_ov))
        {
            output_vector = candidate_ov;
            break;
        }
        else
            continue;
    }

    return output_vector;
}

void GenTestCases(vector<vector<int>> &input_matrix, vector<vector<int>> &output_matrix, GeneratorParameters const &para)
{
    if (para.new_dataset_every_rune)
        srand(time(NULL));

    int cnt_cases = 0;
    int cnt_tries = 0;

    while (cnt_cases < para.num_of_cases && cnt_tries < para.max_numer_of_input_tries)
    {

        vector<int> input_vector; //
        while (true)
        {
            cnt_tries++;

            auto candidate_iv = GenVectorPerValueRange(para.input_vector_value_range);
            Debug("candidate_iv");
            DebugCollection(candidate_iv);

            if (IsValidInputVector(candidate_iv))
            {
                auto candidate_ov = FindResult(candidate_iv, para);
                input_matrix.push_back(candidate_iv);
                output_matrix.push_back(candidate_ov);
                cnt_cases++;
                break;
            }
            else
                continue;
        }
    }
}

int main()
{
    vector<vector<int>> input, output;

    GeneratorParameters para;
    para.input_vector_value_range = {
        {1, 10},
        {1, 10},
        {1, 10},
        {1, 10},
        {1, 10},
        {1, 10},
        {1, 10},
        {1, 10},
        {1, 10},
        {1, 10},
    }; //e.g. 5 peaks, each peack with 2 values

    para.output_vector_value_range = {
        {1, 6},
    }; // e.g. possible number of peaks values are 1, 2, 3, 4, 5

    //
    para.new_dataset_every_rune = true;

    para.num_of_cases = 20;

    GenTestCases(input, output, para);
    Debug2DCollection(input);
    Debug2DCollection(output);

    for(int i = 1; i <= input.size(); i++)
    {
        string file_name = "I." + to_string(i);
        ofstream fout(file_name);

        vector<vector<int>> mountains =  SplitVector(input[i-1], 2);
        
        fout << mountains.size() << endl;
        for(auto m : mountains)
            fout << m[0] << " " << m[1] << endl;
        fout.close();
    }

    for(int i = 1; i <= output.size(); i++)
    {
        string file_name = "O." + to_string(i);
        ofstream fout(file_name);
        
        fout << output[i-1][0] << endl;
        fout.close();
    }
    return 0;
}
