#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void read_from_file(const string& filename, stringstream& buffer) {
  ifstream file;
  file.open(filename);
  if(!file){
    		cout << "Error opening the file, the program will end with no file.\n";

  }

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
  const int max_blue  =14;
  const int max_green = 13;
  const int max_red = 11; 
  long sum = 0;
  int game =0;
  int number;
  bool possible = true; 
  bool ignore = true;
  while (buffer >> line) {
    if(line == "Game"){
      if(possible){
        sum += game;
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
  return sum;
}
int main() {
    ofstream myfile;
  myfile.open ("example.txt");
  myfile << "Writing this to a file.\n";
  myfile.close();
  return 0;
  cout << part1() << endl;
}