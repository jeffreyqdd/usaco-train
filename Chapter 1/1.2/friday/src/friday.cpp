/*
ID: jeffrey66
TASK: friday
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;


int n;	//n number of years
int yearCnt = 1900;


int dayCnt[7] = {0,0,0,0,0,0,0}; //counter
int monthD[12] = {31,28,31,30,31,30,31,31,30,31,30,31}; //days in a month

int checkLeap(int y){
	return y%4 == 0 && (y%100 != 0 || y%400 == 0);
}
int monthLen(int y, int m){
	if (m == 1) return monthD[m] + checkLeap(y);
	else return monthD[m];
}


void solve(){
	int day = 0;
	for (int y = 1900; y < 1900+n; y++){
		for (int m = 0; m < 12; m ++){
			dayCnt[day] ++;

			day = (day+monthLen(y,m)) % 7;
		}
	}
}

int main(){

	ifstream fin("friday.in");
	ofstream fout("friday.out");

	if(!fin.is_open()) cout << "error\n";


	fin >> n;

	fin.close();

	solve();

	for (int i = 0; i < 6; i++) fout << dayCnt[i] << " ";

	fout << dayCnt[6] << '\n';


	fout.close();


}
