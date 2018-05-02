#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

typedef long long ll;

template <typename T>
bool in_bounds(vector<vector<T>>& grid, int i, int j) {
  return i >= 0 && i < grid.size() && j >= 0 and j < grid[i].size();
}

template <typename T>
T val(vector<vector<T>>& grid, int i, int j, T defaultValue) {
  return in_bounds(grid, i, j) ? grid[i][j] : defaultValue;
}

template <typename T>
void dependency(vector<vector<T>>& grid, int i, int j, T value) {
  grid[i][j] = min(min(
      val(grid, i, j-1, numeric_limits<T>::max()),
      val(grid, i-1, j, numeric_limits<T>::max())),
      val(grid, i+1, j, numeric_limits<T>::max())
    ) + value;
}

int main() {
  int n;
  cin >> n;
  vector<vector<ll>> grid(n, vector<ll>(n, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> grid[i][j];
    }
  }

  vector<vector<ll>> dp(n, vector<ll>(n, numeric_limits<ll>::max()));
  for (int i = 0; i < n; i++) {
    dp[i][0] = grid[i][0];
  }
  for (int j = 1; j < n; j++) {
    for (int i = 0; i < n; i++) {
      dependency(dp, i, j, grid[i][j]);
    }
    for (int i = n-1; i >= 0; i--) {
      dependency(dp, i, j, grid[i][j]);
    }
  }

  ll mn = numeric_limits<ll>::max();
  for (int i = 0; i < n; i++) {
    mn = min(mn, dp[i][n-1]);
  }
  cout << mn << endl;

  return 0;
}
