#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class BIT
{
private:
    int m_size;
    vector<int> m_tree;
public:
    BIT(int size)
    {
        m_size = size;
        m_tree.assign(size + 1,0);
    }
    //arr[x] += v;
    void update_tree(int x, int v)
    {
        for(int idx = x + 1; idx <= m_size; idx += idx & (-idx))
            m_tree[idx] += v;
    }


    /* returns sum of arr[i] where 0 <= i <= x */
    int get_sum(int x)
    {
        int sum = 0;
        
        for(int idx = x + 1; idx > 0; idx -= idx & (-idx))
            sum += m_tree[idx];

        return sum;
    }

};

struct Node
{
    int height, index;

    Node(int h, int i): height(h), index(i) {}

    bool operator<(const Node &n) const
    {
        return height < n.height;
    }   
};


int main()
{
    ifstream fin("bphoto.in");
    ofstream fout("bphoto.out");

    /*
    * read in the cows and sort them by descending height
    * keep track of original index
    */

    int kCows; fin >> kCows;
    vector<Node> line;
    for(int i = 0; i < kCows; i++)
    {
        int h; fin >> h;
        line.push_back(Node(h,i));
    }
    sort(line.rbegin(), line.rend());
    fin.close();
    BIT photo(kCows);
    int unbalanced = 0, seen = 0;
    for(Node n : line)
    {
        int left = photo.get_sum(n.index);
        int right = seen - left;

        if(max(left,right) > min(left,right) * 2)
            unbalanced++;
        photo.update_tree(n.index, 1);
        seen++;
    }
    fout << unbalanced << endl;
    fout.close();

    return 0;
}