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

int part1() {
  std::stringstream buffer;
  read_from_file("/home/mateusz/AdventOfCode2023/Day02/input.txt", buffer);
  vector<int> values;
  string line;
  const int max_blue  =14;
  const int max_green = 13;
  const int max_red = 12; 
  long sum = 0;
  int game =0;
  int number;
  bool possible = true; 
  bool ignore = true;
  while (buffer >> line) {
    if(line == "Game"){
      if(possible){
        sum += game;
      }else{
        possible = true;
      }
      game++;
      ignore = true;
    }
    else if(line == "blue," || line == "blue;" || line == "blue"){
      if(number > max_blue){
        possible = false;
      }
    }
    else if(line == "red," || line == "red;" || line == "red"){
      if(number > max_red){
        possible = false;
      }
    }
    else if(line == "green," || line == "green;" || line == "green"){
      if(number > max_green){
        possible = false;
      }
    }
    else{
      if(!ignore){
        number = stoi(line);
      }
      else{
        ignore = false;
      }
    }
  }
  if(possible){
    sum += game;
  }
  return sum;
}
int part2() {
  std::stringstream buffer;
  read_from_file("/home/mateusz/AdventOfCode2023/Day02/input.txt", buffer);
  vector<int> values;
  string line;
   int max_blue  =0;
   int max_green = 0;
   int max_red = 0; 
  long sum = 0;
  int number;
  bool ignore = true;
  while (buffer >> line) {
    if(line == "Game"){
      sum += max_blue*max_red*max_green;
      max_blue  =0;
      max_green = 0;
     max_red = 0; 
      ignore = true;
    }
    else if(line == "blue," || line == "blue;" || line == "blue"){
      if(number > max_blue){
        max_blue = number;
      }
    }
    else if(line == "red," || line == "red;" || line == "red"){
      if(number > max_red){
        max_red = number;
      }
    }
    else if(line == "green," || line == "green;" || line == "green"){
      if(number > max_green){
        max_green = number;
      }
    }
    else{
      if(!ignore){
        number = stoi(line);
      }
      else{
        ignore = false;
      }
    }
  }
  
  sum += max_blue*max_red*max_green;
  return sum;
}
int main() {
  // cout << part1() << endl;
  cout << part2() << endl;
}