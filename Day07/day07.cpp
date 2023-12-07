#include <algorithm>
#include <fstream>
#include <iostream>
// #include <numeric>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void read_from_file(const string& filename, stringstream& buffer) {
  ifstream file(filename);
  if (file) {
    buffer << file.rdbuf();
    file.close();
  }
}

class CamelCards {
 private:
  map<char, int8_t> mapper = {
      {'2', 2}, {'3', 3},  {'4', 4},  {'5', 5},  {'6', 6},  {'7', 7}, {'8', 8},
      {'9', 9}, {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13}, {'A', 14}};
  string card_string;
  vector<char> cards;
  int32_t bid;
  map<char, int8_t> occurance_map;
  int8_t points;
  int32_t rank;

 public:
  CamelCards(string& cards_string, const int32_t& bid_value)
      : card_string(cards_string), bid(bid_value) {
    points = 0;
    for (char& c : card_string) {
      cards.emplace_back(c);
    }
    calculateOccurence();

    if (checkForNumOfOccurance(5)) {
      points = 7;
    } else if (checkForNumOfOccurance(4)) {
      points = 6;
    } else if (checkForNumOfOccurance(2, 3)) {
      points = 5;
    } else if (checkForNumOfOccurance(3)) {
      points = 4;
    } else if (checkForNumOfOccurance(2, 2)) {
      points = 3;
    } else if (checkForNumOfOccurance(2)) {
      points = 2;
    } else if (checkForHighCard()) {
      points = 1;
    }
  }

  void calculateOccurence() {
    for (char& c : cards) {
      occurance_map[c]++;
    }
  }
  bool checkForNumOfOccurance(int8_t how_many_occursion) const {
    for (auto const& x : occurance_map) {
      if (x.second == how_many_occursion) {
        return true;
      }
    }
    return false;
  }
  bool checkForNumOfOccurance(int8_t how_many_occursion,
                              int8_t how_many_occursion2) const {
    bool first = false;
    map<char, int8_t> occurance_map_copy = occurance_map;
    for (auto& x : occurance_map_copy) {
      if (x.second == how_many_occursion) {
        first = true;
        occurance_map_copy.erase(x.first);
        break;
      }
    }

    for (auto& x : occurance_map_copy) {
      if (x.second == how_many_occursion2) {
        return first;
      }
    }
    return false;
  }
  bool checkForHighCard() {
    for (auto const& x : occurance_map) {
      if (x.second != 1) {
        return false;
      }
    }
    return true;
  }
  void setRank(int32_t rank) { this->rank = rank; }
  int32_t getRank() const { return this->rank; }
  int32_t getBid() const { return this->bid; }
  friend bool cmp(CamelCards& a, CamelCards& b);
};

bool cmp(CamelCards& a, CamelCards& b) {
  int i = 0;
  if (a.points == b.points) {
    while (a.cards[i] == b.cards[i]) {
      i++;
    }
    return a.mapper[a.cards[i]] < b.mapper[b.cards[i]];
  } else {
    return a.points < b.points;
  }
}
int part1() {
  std::stringstream buffer;
  read_from_file("/home/mateusz/AdventOfCode2023/Day07/input.txt", buffer);
  string cards, bid;
  vector<CamelCards> vec;
  while (buffer >> cards >> bid) {
    vec.push_back(CamelCards(cards, stoi(bid)));
  }
  sort(vec.begin(), vec.end(), cmp);
  for(int i =0; i<vec.size(); ++i){
    vec[i].setRank(i+1);
  }
  long long anwser = 0;
  for(int i =0; i<vec.size(); ++i){
    anwser += vec[i].getBid() * vec[i].getRank();
  }

  return anwser;
}

int main() {
  cout << part1() << endl;
  // cout << part2() << endl;
}