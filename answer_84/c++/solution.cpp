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

// thanks AndyV! https://stackoverflow.com/questions/1640258/need-a-fast-random-generator-for-c
// This function is a nice quick random number generator with a period of 2^96-1
unsigned long xorshf96(void) {
  static unsigned long x=123456789, y=362436069, z=521288629;
  unsigned long t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;

   t = x;
   x = y;
   y = z;
   z = t ^ x ^ y;

  return z;
}

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
  ll total_land_counts = 0;
  vector<ll> land_counts = vector<ll>(40, 0);
  vector<pair<ll, string>> squares = {
    {0, "GO"}, {0, "A1"}, {0, "CC1"}, {0, "A2"}, {0, "T1"}, {0, "R1"}, {0, "B1"}, {0, "CH1"}, {0, "B2"}, {0, "B3"},
    {0, "JAIL"}, {0, "C1"}, {0, "U1"}, {0, "C2"}, {0, "C3"}, {0, "R2"}, {0, "D1"}, {0, "CC2"}, {0, "D2"}, {0, "D3"},
    {0, "FP"}, {0, "E1"}, {0, "CH2"}, {0, "E2"}, {0, "E3"}, {0, "R3"}, {0, "F1"}, {0, "F2"}, {0, "U2"}, {0, "F3"},
    {0, "G2J"}, {0, "G1"}, {0, "G2"}, {0, "CC3"}, {0, "G3"}, {0, "R4"}, {0, "CH3"}, {0, "H1"}, {0, "T2"}, {0, "H2"}
  };
  // 0 -> nothing special, 1 -> GO, 2 -> JAIL, 3 -> C1, 4 -> E3
  // 5 -> H2, 6 -> R1, 7 -> next_R, 8 -> next_U, 9 -> go back 3 sq
  vector<int> community_chest = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2};
  int community_chest_card_counter = 0;
  vector<int> chance = {0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 8, 9};
  int chance_card_counter = 0;

  bool done = true;
  int dice_sides;
  int k_display;
  int space;
  int double_jail;

  template <typename T>
  void shuffle_cards(vector<T>& cards) {
    random_shuffle(cards.begin(), cards.end());
  }

  int draw_card(int space, const vector<int>& cards, int& card_counter) {
    int c = cards[card_counter];
    // cout << "OOh you drew a card=" << c << " from " << cards.back() << endl;
    card_counter = (card_counter + 1) % cards.size();
    int d;
    switch (c) {
    case 0:
      return space;
    case 1:
      return 0; // GO
    case 2:
      return 10; // JAIL
    case 3:
      return 11; // C1
    case 4:
      return 24; // E3
    case 5:
      return 39; // H2
    case 6:
      return 5; // R1
    case 7:
      d = 10 - ((space + 5) % 10);
      return (space + d) % squares.size(); // next rail road
    case 8:
      return (space > 12 && space < 28) ? 28 : 12;
    case 9:
      // cout << "--------------------------------------" << endl;
      //   cout << "--------------------------------------" << endl;
      //     cout << "--------------------------------------" << endl;
      //       cout << "--------------------------------------" << endl;
      //         cout << "--------------------------------------" << endl;
      //           cout << "--------------------------------------" << endl;
      //             cout << "--------------------------------------" << endl;
      //               cout << "--------------------------------------" << endl;
      //                 cout << "--------------------------------------" << endl;
      done = false;
      space -= 3;
      return space < 0 ? space + squares.size() : space;
    default:
      cout << "Card draw failed" << endl;
      return -1;
    }
  }

  int roll(int d, bool& doubles) {
    int d1 = xorshf96() % d + 1;
    int d2 = xorshf96() % d + 1;
    doubles = d1 == d2;
    return d1 + d2;
  }

  int event(int space) {
    if (!done) {
      done = true;
      switch (space) {
      case 2: // CC1
        return event(draw_card(space, community_chest, community_chest_card_counter));
      case 7: // CH1
        return event(draw_card(space, chance, chance_card_counter));
      case 17: // CC2
        return event(draw_card(space, community_chest, community_chest_card_counter));
      case 22: // CH2
        return event(draw_card(space, chance, chance_card_counter));
      case 30: // G2J -> Go to Jail!
        return 10;
      case 33: // CC3
        return event(draw_card(space, community_chest, community_chest_card_counter));
      case 36: // CH3
        return event(draw_card(space, chance, chance_card_counter));
      default:
        return space;
      }
    }
    else {
      return space;
    }
  }

  void simulate(ll rolls) {
    shuffle_cards(community_chest);
    community_chest_card_counter = 0;
    shuffle_cards(chance);
    chance_card_counter = 0;
    space = 0;
    double_jail = 0;
    for (ll i = 0; i < rolls; i++) {
      bool doubles = false;
      int ddd = roll(dice_sides, doubles);
      if (doubles) {
        double_jail += 1;
        if (double_jail == 3) {
          double_jail = 0;
          space = 10;
          get<0>(squares[space]) += 1;
          continue;
        }
      }
      else {
        double_jail = 0;
      }
      // cout << "You rolled a " << ddd << endl;
      space = (space + ddd) % squares.size();
      // cout << "You landed on " << space << "=" << get<1>(squares[space]) << endl;
      done = false;
      space = event(space);
      // cout << "You ended on " << space << "=" << get<1>(squares[space]) << endl;
      get<0>(squares[space]) += 1;
    }
  }

public:
  ProjectEuler84(int n, int k) {
    dice_sides = n;
    k_display = k;
    ll times = 10000000;
    ll rolls = 1000;

    // vector<int> dices(14, 0);

    bool duf;
    for (ll i = 0; i < times; i++) {
      // dices[roll(6, duf)]++;
      simulate(rolls);
      // cout << "simulation " << i << " is done" << endl << "-----------------------------------" << endl << endl;
    }

    // for (int i = 0; i < dices.size(); i++) {
    //   cout << i << " " << dices[i] / (double)times << "\t" << i / 36.0<< endl;
    // }

    sort(squares.rbegin(), squares.rend());
  }

  void print_result(ostream& out) {
    vector<string> results(k_display);
    for (int i = 0; i < k_display; i++) {
      cout << get<0>(squares[i]) / 10000000000.0 << " " << get<1>(squares[i]) << endl;
      results[i] = get<1>(squares[i]);
    }
    out << join(results, " ") << endl;
  }
};


int main() {
  int n, k;
  cin >> n >> k;
  ProjectEuler84 pe84(n, k);
  pe84.print_result(cout);
}
