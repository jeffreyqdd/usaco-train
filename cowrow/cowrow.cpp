/*
ID: jeffrey66
TASK: beads
LANG: C++
*/

#include <iostream>
#include <fstream>
using namespace std;

int kTotalCow, cow_id[1000];

int main(){
	ifstream fin("cowrow.in");
	ofstream fout("cowrow.out");
	fin>>kTotalCow;
	for(int i=0; i<kTotalCow; i++){
		fin >> cow_id[i];
	}
	fin.close();

	//simple O(n^2) solve
	int included_id, removed_id,best = 0;

	for(int i=0; i<kTotalCow; i++){
		//set up test
		int count = 0;
		included_id = cow_id[i];
		removed_id=0;


		for(int j=i; j<kTotalCow; j++){

			if(included_id != cow_id[j]){
				if (removed_id == 0) removed_id=cow_id[j];
				else if(removed_id != cow_id[j])break;
			}

			if(included_id == cow_id[j]) count++;
		}
		//cout<< count << endl;

		best = max(best,count);
	}

	fout<<best<<endl;
    return 0;
}
