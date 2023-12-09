#include <algorithm>
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

void read_elements(vector<vector<int64_t>>& all_numbers) {
  std::stringstream buffer;
  read_from_file("/home/mateusz/AdventOfCode2023/Day09/input.txt", buffer);
  string line;
  while (getline(buffer, line)) {
    stringstream ss;
    vector<int64_t> tmp;
    int64_t number;
    ss << line;
    while (ss >> number) {
      tmp.emplace_back(number);
    }
    all_numbers.emplace_back(tmp);
  }
}
bool all_zeros(const vector<int64_t>& vec) {
  bool all_zero = true;
  for (const int64_t& number : vec) {
    if (number != 0) {
      return false;
    }
  }
  return true;
}
int64_t extrapolate(vector<int64_t>& vec) {
  vector<vector<int64_t>> calculated_numbers{vec};

  while (calculated_numbers.back().back() != 0) {
    vector<int64_t> tmp;
    for (int i = 0, j = 1; j < calculated_numbers.back().size(); ++i, ++j) {
      tmp.emplace_back(calculated_numbers.back()[j] -
                       calculated_numbers.back()[i]);
    }
    calculated_numbers.emplace_back(tmp);
  }

  for (int i = calculated_numbers.size() - 1; i >= 1; --i) {
    calculated_numbers[i - 1].push_back(calculated_numbers[i - 1].back() +
                                        calculated_numbers[i].back());
  }
  return calculated_numbers[0].back();
}
int part1() {
  vector<vector<int64_t>> all_numbers;
  read_elements(all_numbers);
  int64_t sum = 0;
  for (auto& vec : all_numbers) {
    sum += extrapolate(vec);
  }
  return sum;
}

int64_t extrapolate_backwards(vector<int64_t>& vec) {
  vector<vector<int64_t>> calculated_numbers{vec};

  while (calculated_numbers.back().back() != 0) {
    vector<int64_t> tmp;
    for (int i = 0, j = 1; j < calculated_numbers.back().size(); ++i, ++j) {
      tmp.emplace_back(calculated_numbers.back()[j] -
                       calculated_numbers.back()[i]);
    }
    calculated_numbers.emplace_back(tmp);
  }

  for (int i = calculated_numbers.size() - 1; i >= 1; --i) {
    calculated_numbers[i - 1].insert(
        calculated_numbers[i - 1].begin(),
        calculated_numbers[i - 1].front() - calculated_numbers[i].front());
  }
  return calculated_numbers[0].front();
}
int part2() {
  vector<vector<int64_t>> all_numbers;
  read_elements(all_numbers);
  int64_t sum = 0;
  for (auto& vec : all_numbers) {
    sum += extrapolate_backwards(vec);
  }

  return sum;
}
int main() {
  // cout << part1() << endl;
  cout << part2() << endl;
}