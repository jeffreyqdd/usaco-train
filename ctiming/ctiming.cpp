#include <iostream>
#include <fstream>
using namespace std;


int tot_min(int d, int h, int m)
{
	return d * 1440 + h + 60 + m; 
}

int main()
{
	ifstream fin("ctiming.in");
	ofstream fout("ctiming.out");

	int day, hour, minute;
	
	fin >> day >> hour >> minute;

	fin.close();

	if( tot_min(day, hour, minute) - tot_min(11,11,11) < 0)
		fout <<  -1;

	else
		fout <<  tot_min(day, hour, minute);
	
	fout.close();

	return 0;
}
