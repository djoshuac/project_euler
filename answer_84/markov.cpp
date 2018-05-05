#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include <string>
#include <sstream>
using namespace std;

typedef long long ll;


template <typename T>
string join(const vector<T>& v, string d) {
  // Thanks Brian R. Bondy! https://stackoverflow.com/questions/1430757/c-vector-to-string
  stringstream ss;
  for(size_t i = 0; i < v.size(); ++i) {
    if(i != 0)
      ss << d;
    ss << v[i];
  }
  return ss.str();
}

// Monopoly
class ProjectEuler84 {
private:
  vector<string> names = {
    "GO", "A1", "CC1", "A2", "T1", "R1", "B1", "CH1", "B2", "B3",
    "JAIL", "C1", "U1", "C2", "C3", "R2", "D1", "CC2", "D2", "D3",
    "FP", "E1", "CH2", "E2", "E3", "R3", "F1", "F2", "U2", "F3",
    "G2J", "G1", "G2", "CC3", "G3", "R4", "CH3", "H1", "T2", "H2"
  };
  vector<vector<double>> transition_matrix;
  vector<vector<double>> markov_matrix;
  vector<pair<double, string>> results;
  vector<double> probability_vector;

  vector<double> D;
  int k_display;
  int dice_sides;

  bool isCommunityChest(int s) {
    return s == 2 || s == 17 || s == 33;
  }

  bool isChance(int s) {
    return s == 7 || s == 22 || s == 36;
  }

  int nextRR(int s) {
    return (s + 10 - ((s + 5) % 10)) % 40;
  }

  int nextUU(int s) {
    return (s > 12 && s < 28) ? 28 : 12;
  }

  void initializeDice(int d) {
    D = vector<double>(40, 0.0);
    int c = 1;
    for (int i = 2; i <= d + 1; i++) {
      D[i % 40] += c / static_cast<double>(d*d);
      c += 1;
    }
    c -= 2;
    for (int i = d + 2; i <= 2*d; i++) {
      D[i % 40] += c / static_cast<double>(d*d);
      c -= 1;
    }
    // D[2] = D[12] = 1 / 36.0;
    // D[3] = D[11] = 2 / 36.0;
    // D[4] = D[10] = 3 / 36.0;
    // D[5] = D[9] = 4 / 36.0;
    // D[6] = D[8] = 5 / 36.0;
    // D[7] = 6 / 36.0;
  }

  void buildInitialTransitionMatrix() {
    transition_matrix = vector<vector<double>>(40, vector<double>(40, 0.0));
    for (size_t i = 0; i < names.size(); i++) {
      if (i == 30) {
        transition_matrix[30][30] = 1;
        continue;
      }
      for (size_t j = 0; j < names.size(); j++) {
        double d = D[j];
        if (d > 0.0) {
          int s = (j + i) % 40;
          if (isCommunityChest(s)) {
            transition_matrix[i][s] += 14 * d / 16;
            transition_matrix[i][0] += d / 16;
            transition_matrix[i][10] += d / 16;
          }
          else if(isChance(s)) {
            transition_matrix[i][s] += 6 * d / 16;
            transition_matrix[i][0] += d / 16;
            transition_matrix[i][10] += d / 16;
            transition_matrix[i][11] += d / 16;
            transition_matrix[i][24] += d / 16;
            transition_matrix[i][39] += d / 16;
            transition_matrix[i][5] += d / 16;
            transition_matrix[i][nextRR(s)] += 2 * d / 16;
            transition_matrix[i][nextUU(s)] += d / 16;
            if (s != 36) {
              transition_matrix[i][s - 3 >= 0 ? s - 3 : s - 3 + 40] += d / 16;
            }
            else {
              transition_matrix[i][s-3] += 14 * d / 16 / 16;
              transition_matrix[i][0] += d / 16 / 16;
              transition_matrix[i][10] += d / 16 / 16;
            }
          }
          else if (s == 30) {
            transition_matrix[i][10] += d;
          }
          else {
            transition_matrix[i][s] += d;
          }
        }
      }
    }
  }

  vector<vector<double>> multiply_matrices(const vector<vector<double>>& left, const vector<vector<double>>& right) {
    vector<vector<double>> result(left.size(), vector<double>(right[0].size(), 0.0));
    for (size_t i = 0; i < left.size(); i++) {
      for (size_t j = 0; j < right[0].size(); j++) {
        for (size_t k = 0; k < right.size(); k++) {
          result[i][j] += left[i][k] * right[k][j];
        }
      }
    }
    return result;
  }

  vector<double> multiply(const vector<double>& vect, const vector<vector<double>>& matrix) {
    vector<double> result(vect.size(), 0.0);
    for (int i = 0; i < vect.size(); i++) {
      for (int j = 0; j < matrix.size(); j++) {
        result[i] += vect[j] * matrix[j][i];
      }
    }
    return result;
  }

  void iterations(int n) {
    markov_matrix = transition_matrix;
    probability_vector = vector<double>(names.size(), 0.0);
    probability_vector[0] = 1.0;
    for (int i = 0; i < n; i++) {

      // for (int i = 0; i < markov_matrix.size(); i++) {
      //   cout << names[i];
      //   cout << markov_matrix[i][0];
      //   for (int j = 1; j < markov_matrix.size(); j++) {
      //     cout << " " << markov_matrix[i][j];
      //   }
      //   cout << endl;
      // }

      probability_vector = multiply(probability_vector, transition_matrix);
      // markov_matrix = multiply_matrices(markov_matrix, transition_matrix);
    }
  }

  void computeProbabilities() {
    for (size_t i = 0; i < names.size(); i++) {
      results.emplace_back(probability_vector[i], names[i]);
    }
    sort(results.rbegin(), results.rend());
  }

public:
  ProjectEuler84(int n, int k) {
    dice_sides = n;
    k_display = k;

    initializeDice(dice_sides);
    buildInitialTransitionMatrix();
    iterations(50000);
    computeProbabilities();
  }

  void print_result(ostream& out) {
    vector<string> topK(k_display);
    for (int i = 0; i < k_display; i++) {
      topK[i] = get<1>(results[i]);
      // cout << get<1>(results[i]) << " " << get<0>(results[i]) << endl;
    }
    out << join(topK, " ") << endl;
  }
};


int main() {
  int n, k;
  cin >> n >> k;
  ProjectEuler84 pe84(n, k);
  pe84.print_result(cout);
}
