/*
ID: jeffrey66
TASK: ride
LANG: C++
*/

#include <iostream>
#include <fstream>


using namespace std;

//var
char comet[10];
char group[10];


using namespace std;

int solve(char *c){
	int i,j;
	j=1;

	for (i = 0; c[i] && isalpha(c[i]);i++){
		j = ((c[i] - 'A' + 1) * j) % 47;
	}

	return j;
}


int main() {
	//read
	ifstream fin("ride.in");
	ofstream fout("ride.out");

	fin >> comet >> group;

	fin.close();

	if (solve(comet) == solve(group) ){
		fout << "GO" << '\n';
	} else {
		fout << "STAY" << '\n';
	}

	fout.close();
	return 0;
}
