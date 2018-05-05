#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

int MAX = 5000000;

vector<int> counts(MAX+1, 0);
vector<int> bests(MAX+1, -1);

int gcd(int n, int m) {
  return m == 0 ? n : gcd(m, n % m);
}

void preprocess() {
  int a, b, c;
  int aa, bb, cc;
  for (int n = 1; n*n < MAX ; n++) {
    for (int m = n + 1; 2*m*m <= MAX; m += 2) {
      if (gcd(m, n) != 1) {
        continue;
      }
      a = m*m - n*n;
      b = 2*m*n;
      c = m*m + n*n;
      aa = a;
      bb = b;
      cc = c;
      for (int k = 1; aa + bb + cc <= MAX; k++) {
        counts[aa + bb + cc] += 1;
        aa += a;
        bb += b;
        cc += c;
      }
    }
  }


  int best = 0;
  int count = 0;
  for (int i = 0; i <= MAX; i++) {
    if (count < counts[i]) {
      best = i;
      count = counts[i];
      // cout << best << " " << count << endl;
    }
    bests[i] = best;
  }
}

void solution(int n, ostream& out) {
  out << bests[n] << endl;
}

int main() {
  preprocess();
  int t, n;
  cin >> t;
  for (int i = 0; i < t; i++) {
    cin >> n;
    solution(n, cout);
  }

  return 0;
}
