#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

int main() {
  int n;
  cin >> n;
  vector<vector<ll>> grid(n, vector<ll>(n, 0l));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> grid[i][j];
    }
  }

  vector<ll> prev(n, 0l);
  vector<ll> dp(n, 0l);
  prev[0] = grid[0][0];
  for (int j = 1; j < n; j++) {
    prev[j] = grid[0][j-1] + grid[0][j];
  }
  for (int i = 1; i < n; i++) {
    dp[0] = prev[0] + grid[i][0];
    for (int j = 1; j < n; j++) {
      dp[j] = max(prev[j-1], prev[j]) + grid[i][j];
    }
    prev = dp;
  }

  cout << dp[n-1] << endl;

  return 0;
}
