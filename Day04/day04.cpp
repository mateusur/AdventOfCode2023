#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void read_from_file(const string& filename, stringstream& buffer) {
  ifstream file(filename);
  if (file) {
    buffer << file.rdbuf();
    file.close();
  }
}

int calculateWorth(int k){
  if(k==0){
    return 0;
  }
  else if(k==1){
    return 1;
  }
  else {
    return calculateWorth(k-1)*2;
  }
}
int part1() {
  std::stringstream buffer;
  read_from_file("/home/mateusz/AdventOfCode2023/Day03/input.txt", buffer);
  vector<int> winning_numbers_vector;
  string line;

  long sum = 0;
  int winning_num =0;
  bool possible = true; 
  bool ignore = true;
  bool winning_numbers = true;

  while (buffer >> line) {
    if(line == "Card"){
      ignore = true;
      winning_numbers_vector.clear();
      sum += calculateWorth(winning_num);
      winning_num=0;
    }
    else if( ignore){
      winning_numbers = true;
      ignore = false;
    }
    else if(line == "|"){
      winning_numbers = false;
    }
    else{
      if(winning_numbers){
        winning_numbers_vector.emplace_back(stoi(line));
      }
      else {
        auto it = find (winning_numbers_vector.begin(), winning_numbers_vector.end(), stoi(line));
        if (it != winning_numbers_vector.end()){
          winning_num++;
        }
      }
    }

  }
  return sum;
}

int part2() {
  std::stringstream buffer;
  read_from_file("/home/mateusz/AdventOfCode2023/Day03/input.txt", buffer);
  vector<int> winning_numbers_vector;
  vector<int> how_many_copies(190,1);

  string line;

  long sum = 0;
  int winning_num =0;
  bool possible = true; 
  bool ignore = true;
  bool winning_numbers = true;
  int card = 0;
  while (buffer >> line) {
    if(line == "Card"){
      ignore = true;
      winning_numbers_vector.clear();
      for(int j=0;j<how_many_copies[card];++j){
        for(size_t i = card+1; i<=card+winning_num;++i){
          how_many_copies[i]++;
        }
      }

      
      winning_num=0;
      card++;
    }
    else if( ignore){
      winning_numbers = true;
      ignore = false;
    }
    else if(line == "|"){
      winning_numbers = false;
    }
    else{
      if(winning_numbers){
        winning_numbers_vector.emplace_back(stoi(line));
      }
      else {
        auto it = find (winning_numbers_vector.begin(), winning_numbers_vector.end(), stoi(line));
        if (it != winning_numbers_vector.end()){
          winning_num++;
        }
      }
    }

  }
  sum = accumulate(how_many_copies.begin()+1,how_many_copies.end(),0);
  return sum;
}

int main() {
  cout << part1() << endl;
  cout << part2() << endl;
}