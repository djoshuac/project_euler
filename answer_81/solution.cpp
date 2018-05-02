#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

int main() {
  ll MAX = 1000000001;
  int n;
  cin >> n;
  vector<ll> dp(n + 1, MAX);
  dp[1] = 0;
  ll aij;
  for (int i = 0; i < n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> aij;
      dp[j] = min(dp[j-1], dp[j]) + aij;
    }
  }

  cout << dp[n] << endl;

  return 0;
}
