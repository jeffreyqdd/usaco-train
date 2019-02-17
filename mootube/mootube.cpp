#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

typedef long long intl;

struct Video
{
    intl id;
    intl rev;
};

int kVideos, kQuestions;

intl Bfs(Video const &video, vector<vector<Video>> const & path)
{
    //input tells the video watched and fj's set revelance
    int set_rev = video.rev;

    //a set tells if a node has already been visited, contains video ids
    bool visited[100001] = {false};

    //counter to count how many videos pass fj's constraints
    intl recommended = 0;

    //this queue contains the id of the video to be searched
    queue<Video> q; 
    q.push(video);

    while(!q.empty())
    {
        //read in first item from queue
        Video item = q.front(); q.pop();
        intl vid_id = item.id, vid_rev = item.rev;

        //for each video : path[video id]
        for(auto v : path[vid_id])
        {
            //if it has been visited, visited[v.id] = true, continue
            if(visited[v.id]) continue;
            //update visited[v.id] = true;
            visited[v.id] = true;

            //check if it statisfies the contraints, v.rev >= set_rev
            if(v.rev >= set_rev)
            {
                //append to recommended vector
                recommended++;
                //search the children of node v
                q.push(v);
            }
        }
    }

    intl zero = 0;
    return max(zero, recommended-1);
}

int main()
{
    ifstream fin("mootube.in");
    ofstream fout("mootube.out");

    fin >> kVideos >> kQuestions;


    //read
    //2d vector video_path
    //video_path[x] yields a vector of struct(Video)
        //video.id, video x can see
        //video.rev, revelance to video x
    
    vector<vector<Video>> video_path(kVideos+1);

    for(int i=0; i<kVideos-1; i++)
    {
        intl v1, v2, revelance; fin >> v1 >> v2 >> revelance;
        video_path[v1].push_back({v2, revelance});
        video_path[v2].push_back({v1, revelance});
    }
    
    //implement a bfs for each of fj's quetions

    //how many vids will be recomened if a cow watches video_i with a revelance of k_rev
    
    for(int q=0; q<kQuestions; q++)
    {
        Video v; fin >> v.rev >> v.id;
        fout << Bfs(v, video_path) << endl;
    }
    
    fin.close();
    fout.close();
    return 0;
}