#include <iostream>
#include <fstream>
using namespace std;

long long fibbonacci(int n)
{
    long long arr[n + 2];

    arr[0] = 0;
    arr[1] = 1;

    for(int i = 2; i <= n; i++)
        arr[i] = arr[i - 1] + arr[i - 2];

    return arr[n];
}

bool subsetSumDynamic(int set[], int n, int sum)
{
  bool subset[n + 1][sum + 1];

  for(int i = 0; i < n + 1; i++) //just like recursive, base case
    subset[i][0] = true;

  for(int i = 1; i < sum + 1; i++) //base casee
    subset[0][i] = false;

  for(int i = 1; i < n + 1; i++)
  {
    for(int j = 1; j < sum + 1; j++)
    {
      if(j < set[i - 1])
        subset[i][j] = subset[i - 1][j];

      else
        subset[i][j] = subset[i - 1][j] || subset[i - 1][j - set[i - 1]];
      
    }
  }

  return subset[n][sum];
  
}


bool subsetSumRecursive(int set[], int n, int sum)
{
  if(sum == 0) return true;
  if(n == 0 && sum != 0) return false;

  if(set[n - 1] > sum)
    subsetSumRecursive(set, n - 1, sum);

  return subsetSumRecursive(set, n - 1, sum) 
          || subsetSumRecursive(set, n - 1, sum - set[n - 1]);
}
int main()
{
    
    //cout << fibbonacci(10) << endl;

    int arr[] = {1, 1, 2, 1, 1, 3};
    cout << subsetSumDynamic(arr, 6,9) << endl;
    cout << subsetSumRecursive(arr, 6,9) << endl;

    return 0;
}
