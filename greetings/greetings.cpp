#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


void tick(int& steps, int& location, int& index_cnt, vector<int>& data){
    if(index_cnt == data.size()){
        if(steps>0){
            steps--;
            location++;
        }
        else if(steps<0){
            steps++;
            location--;
        }
    } else {
        if (steps == 0){
            steps = data[index_cnt];
            index_cnt++;
        }
        if(steps>0){
            steps--;
            location++;
        }
        else if(steps<0){
            steps++;
            location--;
        }   
    }
}
int solve(int max_steps, vector<int> bessie, vector<int> elsie){
    /*
    it is crucial to remember that the cows will greet when they lie on the same x values
    (excluding start at origin)

    they will say hi only if they are previously apart for ex. 3L and 4L will yield 0 greetings

    have two 'pointers' that walk the number line
    */


    //two cows, greetings, and together check;
    int steps_b = 0, location_b = 0, cnt_b = 0;
    int steps_e = 0, location_e = 0, cnt_e = 0;
    bool together = true;

    int greetings = 0;
    for(int t = 1; t<= max_steps; t++){
        //t for time
        //bessie tick
        tick(steps_b,location_b,cnt_b,bessie);
        //elsie tick
        tick(steps_e,location_e,cnt_e,elsie);
 
        if(location_b != location_e) together = false;
        if(location_b == location_e && together == false){
            greetings++;
            together = true;
        }
    }

    return greetings;

}
int main(){
    //read
    ifstream fin("greetings.in");
    ofstream fout("greetings.out");

    //line 1 contains two values, b:#times Bessie moves, e:#times Elsie moves
    int b,e; fin >> b >> e;

    vector<int> bessie_steps;
    vector<int> elsie_steps;
    
    int max_steps = 0;

    int m = 0, n = 0;
    for(int i=0; i<b+e; i++){
        int x; char c;
        fin >> x >> c;
        if(c == 'L') x*=-1;
        
        if(i < b){
            bessie_steps.push_back(x);
            m += abs(x);
        }
        else {
            elsie_steps.push_back(x);
            n += abs(x);
        }
        max_steps = max(m, n);
    }

    fout << solve(max_steps, bessie_steps, elsie_steps) << endl;
    
    return 0;
}