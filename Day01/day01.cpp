#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
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
uint64_t part1() {
  std::stringstream buffer;
  read_from_file("input.txt", buffer);
  vector<int> values;
  string line;
  while (buffer >> line) {
    int i = 0;
    int j = line.size() - 1;
    int i_val = 0;
    int j_val = 0;
    while (i <= j) {
      if (isdigit(line[i]) && i_val == 0) {
        i_val = line[i] - '0';
        if (j_val != 0) {
          break;
        }
      }
      if (isdigit(line[j]) && j_val == 0) {
        j_val = line[j] - '0';
        if (i_val != 0) {
          break;
        }
      }
      if (i_val == 0) {
        i++;
      }
      if (j_val == 0) {
        j--;
      }
    }
    values.emplace_back(i_val * 10 + j_val);
  }
  return accumulate(values.begin(), values.end(), 0);
  ;
}
pair<int, int> find_first(const string& str) {
  const map<string, int> digits{{"one", 1},   {"two", 2},   {"three", 3},
                                {"four", 4},  {"five", 5},  {"six", 6},
                                {"seven", 7}, {"eight", 8}, {"nine", 9}};
  pair<int, int> first_pair{INT32_MAX, -1};
  for (auto [key, value] : digits) {
    size_t pos = str.find(key);
    if (pos != std::string::npos && pos < first_pair.first) {
      first_pair.first = pos;
      first_pair.second = value;
    }
  }
  return first_pair;
}
pair<int, int> find_last(const string& str) {
  static const map<string, int> digits{
      {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9},
  };
  pair<int, int> second_pair{0, -1};
  for (auto [key, value] : digits) {
    size_t pos = str.rfind(key);
    if (pos != std::string::npos && pos > second_pair.first) {
      second_pair.first = pos;
      second_pair.second = value;
    }
  }
  return second_pair;
}
uint64_t part2() {
  std::stringstream buffer;
  read_from_file("input.txt", buffer);
  vector<int> values;
  string line;
  while (buffer >> line) {
    int i = 0;
    int j = line.size() - 1;
    pair<int, int> first = find_first(line);
    pair<int, int> second = find_last(line);
    int i_val = 0;
    int j_val = 0;
    while (i <= j) {
      if (isdigit(line[i]) && i_val == 0) {
        i_val = line[i] - '0';
        if (j_val != 0) {
          break;
        }
      }
      if (isdigit(line[j]) && j_val == 0) {
        j_val = line[j] - '0';
        if (i_val != 0) {
          break;
        }
      }
      if (i_val == 0) {
        i++;
      }
      if (j_val == 0) {
        j--;
      }
    }
    if (first.second != -1 && first.first < i) {
      i_val = first.second;
    }
    if (second.second != -1 && second.first > j) {
      j_val = second.second;
    }
    values.emplace_back(i_val * 10 + j_val);
  }
  uint64_t an = accumulate(values.begin(), values.end(), 0);
  return an;
}
int main() {
  cout << part1() << endl;
  part2();
}