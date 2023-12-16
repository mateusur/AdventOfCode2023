#include <cstddef>
#include <cstdint>
#include <cwchar>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

void print_columnVise(const vector<vector<char>> &all_numbers) {
  for (size_t col = 0; col < all_numbers[0].size(); ++col) {
    for (size_t row = 0; row < all_numbers.size(); ++row) {
      cout << all_numbers[row][col] << endl;
    }
    cout << "-------" << endl;
  }
}
void print(const vector<vector<char>> &all_numbers) {
  for (size_t row = 0; row < all_numbers.size(); ++row) {
    for (size_t col = 0; col < all_numbers[0].size(); ++col) {
      cout << all_numbers[row][col];
    }
    cout << endl;
  }
  cout << endl;
}
void read_from_file(const string &filename, stringstream &buffer) {
  ifstream file(filename);
  if (file) {
    buffer << file.rdbuf();
    file.close();
  }
}

void read_elements(vector<vector<char>> &all_numbers) {
  std::stringstream buffer;
  read_from_file("/home/mateusz/AdventOfCode2023/Day16/input.txt", buffer);
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

int64_t count_points(const vector<vector<char>> &all_numbers) {
  int64_t sum = 0;
  size_t number_of_rows = all_numbers.size();
  for (size_t row = 0; row < number_of_rows; ++row) {
    for (size_t col = 0; col < all_numbers[0].size(); ++col) {
      if (all_numbers[row][col] == 'O') {
        sum += number_of_rows + -row;
      }
    }
  }
  return sum;
}

void path(const vector<vector<char>>& all_numbers, int64_t prev_row, int64_t prev_col,int64_t row, int64_t col,set<tuple<int64_t,int64_t,int64_t,int64_t>>& visited,int64_t num_of_columns,int64_t num_of_rows){
  char c;
  int8_t col_diff;
  int8_t row_diff;
  // const int64_t num_of_columns =all_numbers[0].size();
  // const int64_t num_of_rows = all_numbers.size();
  static int counter;
  counter++;
  cout << counter << endl;
  while ((row>=0 && row<num_of_rows) && (col>=0 && col<num_of_columns)) {
    c = all_numbers[row][col];
    col_diff = col - prev_col;
    row_diff = row - prev_row;
    auto it = visited.insert({row,col,row_diff,col_diff});
    if(it.second == false){
      return;
    }
    prev_col = col;
    prev_row = row;
    switch (c) {
      case '.':
      if(col_diff==1){
        col++;
      }
      else if (col_diff==-1) {
      col--;
      }else if (row_diff==1) {
        row++;
      }else{
        row--;
      }
      break;
      case '/':
      if(col_diff==1){
        row--;
      }
      else if (col_diff==-1) {
      row++;
      }else if (row_diff==1) {
        col--;
      }else{
        col++;
      }
      break;
      case '\\':
      if(col_diff==1){
        row++;
      }
      else if (col_diff==-1) {
      row--;
      }else if (row_diff==1) {
        col++;
      }else{
        col--;
      }
      break;
      case '|':
      if(col_diff==1){
        path(all_numbers, row, col, row+1, col,visited,all_numbers[0].size(),all_numbers.size());
        row--;
      }
      else if (col_diff==-1) {
        path(all_numbers, row, col, row+1, col,visited,all_numbers[0].size(),all_numbers.size());
        row--;
      }else if (row_diff==1) {
        row++;
      }else{
        row--;
      }
      break;
      case '-':
      if(col_diff==1){
        col++;
      }
      else if (col_diff==-1) {
        col--;
      }else if (row_diff==1) {
        path(all_numbers, row, col, row, col+1,visited,all_numbers[0].size(),all_numbers.size());
        col--;
      }else{
        path(all_numbers, row, col, row, col+1,visited,all_numbers[0].size(),all_numbers.size());
        col--;
      }
      break;
    }

  }
  return;
}

int part1() {
  vector<vector<char>> all_numbers;
  read_elements(all_numbers);
  set<tuple<int64_t,int64_t,int64_t,int64_t>> visited;
  path(all_numbers,0,0,0,1,visited,all_numbers[0].size(),all_numbers.size());
  return -1;
}

int main() {
  cout << part1() << endl;
  // cout << part2() << endl;
}