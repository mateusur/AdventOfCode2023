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

pair<int64_t, int64_t> read_elements(vector<vector<char>>& all_numbers) {
  std::stringstream buffer;
  read_from_file("/home/mateusz/AdventOfCode2023/Day10/input.txt", buffer);
  string line;
  int64_t row = 0;
  pair<int64_t, int64_t> cord;
  while (getline(buffer, line)) {
    stringstream ss;
    vector<char> tmp;
    char number;
    ss << line;
    int64_t column = 0;
    while (ss >> number) {
      if (number == 'S') {
        cord = {row, column};
      }
      tmp.emplace_back(number);
      column++;
    }
    all_numbers.emplace_back(tmp);
    row++;
  }
  return cord;
}
int64_t findNext(int64_t prev_row, int64_t prev_column, int64_t row,
                 int64_t column, int64_t step,
                 vector<vector<char>>& all_numbers) {
  char c = all_numbers[row][column];
  step++;
  switch (c) {
    case '|':
      if (prev_row < row) {
        prev_row = row;
        prev_column = column;
        row++;
      } else {
        prev_row = row;
        prev_column = column;
        row--;
      }
      break;
    case '-':
      if (prev_column < column) {
        prev_row = row;
        prev_column = column;
        column++;
      } else {
        prev_row = row;
        prev_column = column;
        column--;
      }
      break;
    case 'L':
      if (prev_row < row) {
        prev_row = row;
        prev_column = column;
        column++;
      } else {
        prev_row = row;
        prev_column = column;
        row--;
      }
      break;
    case 'J':
      if (prev_row < row) {
        prev_row = row;
        prev_column = column;
        column--;
      } else {
        prev_row = row;
        prev_column = column;
        row--;
      }
      break;
    case '7':
      if (prev_row == row) {
        prev_row = row;
        prev_column = column;
        row++;
      } else {
        prev_row = row;
        prev_column = column;
        column--;
      }
      break;
    case 'F':
      if (prev_row == row) {
        prev_row = row;
        prev_column = column;
        row++;
      } else {
        prev_row = row;
        prev_column = column;
        column++;
      }
      break;
    case 'S':
      return step;
      break;
  }
  findNext(prev_row, prev_column, row, column, step, all_numbers);
}

int part1() {
  vector<vector<char>> all_numbers;
  pair<int64_t, int64_t> cord = read_elements(all_numbers);
  int64_t s1 = findNext(cord.first, cord.second, cord.first, cord.second - 1, 0,
                        all_numbers);
  int64_t s2 = findNext(cord.first, cord.second, cord.first + 1, cord.second, 0,
                        all_numbers);
  return (s1 + s2) / 2;
}

int main() {
  cout << part1() << endl;
  // cout << part2() << endl;
}