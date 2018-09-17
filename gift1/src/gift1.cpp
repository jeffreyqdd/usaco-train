/*
ID: jeffrey66
TASK: gift1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
using namespace std;
//GLOBALS
vector<string> nameList;
map<string,int> people;
int main(){
	//read
	ifstream fin("gift1.in");
	ofstream fout("gift1.out");
	if(!fin.is_open()){
		cout << "somthing went wrong\n";
	};
	int x;
	string y;
	fin >> x;
	for (int i = 0; i<x ; i++){
		fin >> y;
		nameList.push_back(y);
		people[y] = 0;
	};
	//solve
	string name;
	int giftAmount, giftPeople; //amount of money and number of people to receive gifts
	int size, remainder;

	while(!fin.eof()){
		//read and calculate
		fin >> name >> giftAmount >> giftPeople;
		if(giftPeople == 0) continue;
		size = giftAmount / giftPeople;
		remainder = giftAmount % giftPeople;
		//deduct;


		people[name] = people[name] - giftAmount + remainder;


		//distribute gifts
		for(int i = 0; i < giftPeople; i++){
			fin >> name;
			//cout<<"giving to " <<name << " ";

			people[name]= people[name] + size;
			//cout<<balance[people[name]]<<endl;
		};
		//cout << endl;
	};

	//cout << balance.size();

	for (int i = 0; i < x; i++){

		fout << nameList[i] << " " << people[nameList[i]] << '\n';
	};

	fin.close();
	fout.close();
	return 0;
}
