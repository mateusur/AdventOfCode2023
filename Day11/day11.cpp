#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
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

void read_elements(vector<vector<char>>& all_numbers) {
  std::stringstream buffer;
  read_from_file("/home/mateusz/AdventOfCode2023/Day11/input.txt", buffer);
  string line;
  while (getline(buffer, line)) {
    stringstream ss;
    vector<char> tmp;
    char number;
    ss << line;
    while (ss >> number) {
      tmp.emplace_back(number);
    }
    all_numbers.emplace_back(tmp);
  }
}

bool are_all_dots(const vector<char>& vec) {
  for (const char& c : vec) {
    if (c == '#') {
      return false;
    }
  }
  return true;
}
void change_horizontal(vector<vector<char>>& all_numbers) {
  vector<size_t> positions;
  vector<char> all_dots(all_numbers[0].size(), '.');
  for (size_t i = 0; i < all_numbers.size(); ++i) {
    if (are_all_dots(all_numbers[i])) {
      all_numbers.insert(all_numbers.begin() + i, all_dots);
      i++;
    }
  }
}

void insertColumn(std::vector<std::vector<char>>& vec, size_t columnIndex) {
  for (size_t i = 0; i < vec.size(); ++i) {
    vec[i].insert(vec[i].begin() + columnIndex, '.');
  }
}

void change_vertical(std::vector<std::vector<char>>& vec) {
  int rows = vec.size();
  int cols = vec[0].size();

  for (int col = 0; col < vec[0].size(); ++col) {
    bool allDots = true;

    for (int row = 0; row < rows; ++row) {
      if (vec[row][col] != '.') {
        allDots = false;
        break;
      }
    }

    if (allDots) {
      // Insert a column of stars before the current column
      for (int row = 0; row < rows; ++row) {
        vec[row].insert(vec[row].begin() + col, '.');
      }
      ++col;  // Move to the next column as we added a column of stars
    }
  }
}
void display2DVector(const std::vector<std::vector<char>>& vec) {
  for (const auto& row : vec) {
    for (char ch : row) {
      std::cout << ch << " ";
    }
    std::cout << std::endl;
  }
}
int part1() {
  vector<vector<char>> all_numbers;
  read_elements(all_numbers);
  int64_t sum = 0;
  change_vertical(all_numbers);
  change_horizontal(all_numbers);
  vector<pair<int64_t, int64_t>> coordinates;
  for (int i = 0; i < all_numbers.size(); ++i) {
    for (int j = 0; j < all_numbers[i].size(); ++j) {
      if (all_numbers[i][j] == '#') {
        coordinates.push_back({i, j});
      }
    }
  }

  for (int i = 0; i < coordinates.size() - 1; ++i) {
    for (int j = i + 1; j < coordinates.size(); ++j) {
      sum += abs(coordinates[i].first - coordinates[j].first) +
             abs(coordinates[i].second - coordinates[j].second);
    }
  }
  return sum;
}

int main() {
  cout << part1() << endl;
  // cout << part2() << endl;
}