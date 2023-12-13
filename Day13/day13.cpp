#include <algorithm>
#include <cstdint>
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
  read_from_file("/home/mateusz/AdventOfCode2023/Day13/input.txt", buffer);
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

int check_vertical(const vector<vector<char>>& all_numbers) {
for(int i=0, k=i+1; k<all_numbers[0].size();++i,++k){
    bool status = true;
    for(int j = 0; j<all_numbers.size(); ++j){
      // cout << all_numbers[j][i] << ' ' << all_numbers[j][k] << endl;
      if(all_numbers[j][i] != all_numbers[j][k]){
        status = false;
        break;
      }
    }
    // cout << "------" << endl;
    if(status){
      return k;
    }
  }
  return 0;
}
int check_horizontal(const vector<vector<char>>& all_numbers) {
for(int i=0,k=i+1 ; k<all_numbers.size();++i,++k){
    bool status = true;
    for(int j = 0; j<all_numbers[0].size(); ++j){
      cout << all_numbers[i][j] << ' ' << all_numbers[k][j] << endl;
      // cout << all_numbers[i][j] << endl;
      if(all_numbers[i][j] != all_numbers[k][j]){
        status = false;
        break;
      }
    }
    // cout << "------" << endl;
    if(status){
      return k;
    }
  }
  return 0;
}


int part1() {
  vector<vector<char>> all_numbers;
  read_elements(all_numbers);
  int64_t vertical  = check_vertical(all_numbers);
  int64_t horizontal  = check_horizontal(all_numbers);
  
  return vertical*100+horizontal;
}

int64_t read_elements2() {
  vector<vector<char>> all_numbers;
  std::stringstream buffer;
  read_from_file("/home/mateusz/AdventOfCode2023/Day13/input.txt", buffer);
  string line;
  int64_t sum = 0;
  bool vertical = true;
  while (getline(buffer, line)) {
    if(line==""){
        if(vertical){
        sum += ( check_vertical(all_numbers));
        vertical = false;
        }else{
        sum += (100* check_horizontal(all_numbers));
        vertical = true;
    }
      
      all_numbers.clear();
      continue;
    }
    stringstream ss;
    vector<char> tmp;
    char number;
    ss << line;
    while (ss >> number) {
      tmp.emplace_back(number);
    }
    all_numbers.emplace_back(tmp);
  }
  
  if(vertical){
    sum += ( check_vertical(all_numbers));
    vertical = false;
  }else{
    sum += (100* check_horizontal(all_numbers));
    vertical = true;
  }
  
  // int64_t vertical  = check_vertical(all_numbers);
  // int64_t horizontal  = check_horizontal(all_numbers);
  // sum += vertical*100+horizontal;
  return sum;
}
int main() {
  cout << read_elements2() << endl;
  // cout << part2() << endl;
}