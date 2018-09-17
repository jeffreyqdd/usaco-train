/*
ID: jeffrey66
TASK: beads
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;







int solve(vector<char> beadTab){
	//we have all the chars in beadTab and we have the # of beads in N

	int N = beadTab.size();

	int pos = 1;
	int pos_b, pos_f;
	char x,y;

	int cnt = 0;
	int maxCnt = 0;

	for (pos = 1; pos <= N; pos++){
		x = beadTab[pos-1];
		y = beadTab[pos%N];

		cout << x << " " << y << endl;

		pos_b = pos-1;
		pos_f = pos%N;

		//scan back;
		while (true){
			if(x == 'w' && beadTab[pos_b] != 'w' ) x = beadTab[pos_b];

			if(x != 'w' && beadTab[pos_b] != x && beadTab[pos_b] != 'w') break;

			pos_b--;

			if(pos_b < 0) pos_b = N-1;

			cnt++;

			if (cnt >= N) break;

			//cout<<x;
		}
		//cout << endl;

		//scan front
		while (true){
			if(y == 'w' && beadTab[pos_f] != 'w' ) y = beadTab[pos_f];

			if(y != 'w' && beadTab[pos_f] != y && beadTab[pos_f] != 'w') break;

			pos_f++;

			if(pos_f >= N) pos_f = 0;

			cnt++;
			if (cnt >= N) break;

			//cout<<y;
				}
		//cout << endl;

		//cout<< cnt << endl;
		maxCnt = max(maxCnt, cnt);

		if (maxCnt>N){
			maxCnt = N;
			break;
		}

		cnt = 0;
	}

	return maxCnt;
}


int main() {
	//read
	ifstream fin("beads.in");
	ofstream fout("beads.out");

	vector<char> beadTab;

	int beadNum = beadTab.size();
	string s;

	fin >> beadNum >> s;


	cout << beadNum << " " << s << endl;

	//split string into individual char in vector beadTab
	for (int i = 0; i < beadNum; i ++){
		beadTab.push_back(s[i]);
	}


	fout << solve(beadTab) << endl;

	fin.close();
	fout.close();
	return 0;
}
