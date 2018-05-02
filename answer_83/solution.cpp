#include <cmath>
#include <cstdio>
#include <limits>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

typedef long long ll;


template <typename T>
class ProjectEuler83 {
private:
  typedef pair<T, int> Node;
  int n;
  vector<T> grid;
  vector<int> directions;

  bool in_bounds(int i, int d) {
    return not (i % n == 0 and d == -1) and
      not ((i+1) % n == 0 and d == 1) and
      i+d >= 0 and i+d < grid.size();
  }

  vector<Node> neighbors(int i) {
    vector<Node> result;
    for (auto &d : directions) {
      int j = i + d;
      if (in_bounds(i, d)) {
        result.emplace_back(grid[j], j);
      }
    }
    return result;
  }

  T dijkstras() {
    vector<bool> visited(grid.size(), false);
    vector<T> distance(grid.size(), numeric_limits<T>::max());
    distance[0] = grid[0];
    priority_queue<Node, vector<Node>, std::greater<Node>> nearest;
    nearest.emplace(distance[0], 0);
    while (not nearest.empty() and not visited.back()) {
      auto curr = nearest.top();
      nearest.pop();
      T dist = get<0>(curr);
      int u = get<1>(curr);

      if (not visited[u]) {
        visited[u] = true;
        for (auto& next : neighbors(u)) {
          T d = get<0>(next) + dist;
          int v = get<1>(next);
          if (d < distance[v]) {
            distance[v] = d;
            nearest.emplace(d, v);
          }
        }
      }
    }

    return distance.back();
  }

public:
  ProjectEuler83(istream& inn, vector<tuple<int, int>> vectorDirections) {
    inn >> n;

    grid = vector<T>(n*n, -1);
    for (int i = 0; i < grid.size(); i++) {
      inn >> grid[i];
    }

    for (auto &d : vectorDirections) {
      directions.emplace_back(get<0>(d)*n + get<1>(d));
    }
  }

  void solution(ostream& out) {
    out << dijkstras() << endl;
  }
};

int main() {
  ProjectEuler83<ll>(cin, {
    {-1, 0}, // left
    {0, -1}, // up
    {1, 0},  // right
    {0, 1}   // down
  }).solution(cout);
}
