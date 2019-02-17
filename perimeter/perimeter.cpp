#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstring>
using namespace std;

struct Blob
{
    int size;
    set<pair<int,int>> blob_coord; 
    
    bool operator<(const Blob &b) const{
        return size > b.size;
    }
};


char grid[1005][1005];
bool seen[1005][1005];
vector<Blob> ice_cream;
int kRows;

//x and y
void FloodFill(int r, int c, int &size, set<pair<int,int>> &coord)
{
    if(seen[r][c]) return;

    //process
    coord.insert({r,c});
    size ++;
    seen[r][c] = true;

    //search
    if(grid[r+1][c] == '#')
        FloodFill(r+1,c,size,coord);

    if(grid[r-1][c] == '#')
        FloodFill(r-1,c,size,coord); 

    if(grid[r][c+1] == '#')
        FloodFill(r,c+1,size,coord);

    if(grid[r][c-1] == '#')
        FloodFill(r,c-1,size,coord);
    
    return;
}

//get the perimeters
int GetPerimeter(set<pair<int,int>> coord_list)
{
    int perimeter = 0;

    for(auto p : coord_list)
    {
        int r = p.first, c = p.second;

        if(grid[r+1][c] == '.')
            perimeter++;

        if(grid[r-1][c] == '.')
            perimeter++;

        if(grid[r][c+1] == '.')
            perimeter++;

        if(grid[r][c-1] == '.')
            perimeter++;
    }

    return perimeter;
}
int main()
{
    ifstream fin("perimeter.in");
    ofstream fout("perimeter.out");

    memset(grid, '.', sizeof(grid));
    //read
    fin >> kRows;
    for(int r = 1; r <= kRows; r++)
        for(int c = 1; c <= kRows; c++)
            fin >> grid[r][c];
    fin.close();
    
    //flood fill to find blobs
    for(int r = 1; r <= kRows; r++)
    {
        for(int c = 1; c <= kRows; c++)
        {            
            if(seen[r][c] || grid[r][c] == '.') continue;
            int area = 0;
            set<pair<int,int>> coordinates;

            FloodFill(r,c, area, coordinates);

            ice_cream.push_back({area, coordinates});
        }
    }
    //sort
    sort(ice_cream.begin(), ice_cream.end());
    /*
    //debug
    for(auto b : ice_cream)
    {
        cout << b.size << ": ";
        for(auto c : b.blob_coord)
            cout << "("<<c.first  << ","<<c.second<<")"<<" ";
        cout << endl;
    }
    for(int r = 0; r <= kRows+1; r++)
    {
        for(int c = 0; c <= kRows+1; c++)
        {            
            cout << grid[r][c] << " ";
        }
        cout << endl;
    }
    */
    int max_area = ice_cream[0].size;
    int max_perimeter = 0;
    for(auto ic : ice_cream)
    {
        if(ic.size != max_area) break;

        max_perimeter = max(max_perimeter, GetPerimeter(ic.blob_coord)); 
    }


    fout << max_area << " "<<max_perimeter << endl;
    fout.close();

    return 0;
}

