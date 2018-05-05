#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

ll MAX = 10000000l;

vector<int> isqrt(MAX+1, -1);
vector<int> counts(MAX+1, 0);
vector<int> best(MAX+1, -1);

void preprocess() {
  for (ll i = 0; i*i <= MAX; i++) {
    isqrt[i*i] = i;
  }

  for (ll i = 1; i*i <= MAX; i++) {
    for (ll j = i; j*j + i*i <= MAX; j++) {
      ll c = i*i + j*j;
      if (isqrt[c] != -1) {
        counts[i + j + isqrt[c]] += 1;
      }
    }
  }

  ll b = 0;
  ll c = 0;
  for (ll i = 0; i <= MAX; i++) {
    if (c < counts[i]) {
      b = i;
      c = counts[i];
      cout << b << " " << c << endl;
    }
    best[i] = b;
  }
}

void solution(ll n, ostream& out) {
  out << best[n] << endl;
}

int main() {
  preprocess();
  ll t, n;
  cin >> t;
  for (ll i = 0; i < t; i++) {
    cin >> n;
    solution(n, cout);
  }

  return 0;
}
