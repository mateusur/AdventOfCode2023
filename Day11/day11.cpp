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

bool are_all_dots(const vector<char>& vec){
  for(const char& c : vec){
    if(c=='#'){
      return false;
    }
  }
  return true;
}
void change_vertical(vector<vector<char>>& all_numbers){
  vector<size_t> positions;
  vector<char> all_dots(all_numbers[0].size(),'.');
  for(size_t i =0;i <all_numbers.size();++i){
    if(are_all_dots(all_numbers[i])){
      // positions.push_back(i);
      all_numbers.insert(all_numbers.begin()+i,all_dots);
      i++;
    }
  }
}

void insertColumn(std::vector<std::vector<char>>& vec, size_t columnIndex) {
    for (size_t i = 0; i < vec.size(); ++i) {
        vec[i].insert(vec[i].begin() + columnIndex, '.');
    }
}
void change_horizontal(vector<vector<char>>& all_numbers){
  vector<size_t> positions;
  vector<char> all_dots(all_numbers.size(),'.');
  for (size_t col = 0; col < all_numbers.size(); ++col) {
    for (const auto& column: all_numbers[col]) {
        if(are_all_dots(column)){
          // positions.push_back(i);
          insertColumn(all_numbers,col);
          col++;
    }
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
  // change_vertical(all_numbers);
  display2DVector(all_numbers);
  cout << "--------------------------------------------"<< endl;
  change_horizontal(all_numbers);
  display2DVector(all_numbers);
  return 0;
}


int main() {
  cout << part1() << endl;
  // cout << part2() << endl;
}