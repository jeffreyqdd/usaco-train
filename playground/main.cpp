#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 100100
 
int T[MAXN];
 
void inc(int i)
{
	for(i++;i<MAXN;i+=(i&-i))
		T[i]++;
}
 
int getSum(int i)
{
	int c = 0;
	for(i++;i>0;i-=(i&-i))
		c += T[i];
	return c;
}
 
 
int p[MAXN];
 
int main()
{
	int N;
	cin >> N;
	for(int i=0;i<N;i++)
	{
		cin >> p[i];
		p[i]--;
	}

    cout << "==== ";
    for(int i = 0; i < N; i++)
        cout << p[i] << ' ';
    cout << endl;


	int j = N-1;
	while(j > 0 && p[j-1] < p[j])
		j--;

	cout << j << '\n';
	for(int i=j;i<N;i++)
    {
        cout << "incrementing index: " << i << endl;
		inc(p[i]);
    }

    cout << "== ";
    for(int i = 0; i < N; i++)
        cout << getSum(p[i]) <<  " ";
    cout << endl;
        
	for(int i=0;i<j;i++)
	{
		cout << (j - 1 - i) + getSum(p[i]);
		if(i < j - 1) cout << ' ';
		inc(p[i]);
	}
	cout << '\n';
	return 0;
}