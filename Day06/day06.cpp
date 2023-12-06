#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
using namespace std;

void read_from_file(const string& filename, stringstream& buffer) {
  ifstream file(filename);
  if (file) {
    buffer << file.rdbuf();
    file.close();
  }
}

int64_t calculateOutput(  vector<int64_t>& time,vector<int64_t>&distance ){
  int64_t multipied = 1;
  for(size_t i =0; i<time.size();++i){
    int64_t ways = 0;
    for(int speed = 0; speed <=time[i];++speed){
      int64_t traveled_distance = speed*(time[i]-speed);
      if(traveled_distance > distance[i]){
        ways++;
      }
    }
    // cout <<"ways: "<< ways << '\t';
    if(ways!=0){
      multipied*=ways;
    }
    
  }
  return multipied;
}


int part1() {
  std::stringstream buffer;
  read_from_file("/home/mateusz/AdventOfCode2023/Day06/input.txt", buffer);
  vector<int64_t> time;
  vector<int64_t> distance;

  string line;
  bool reading_time = true;
  bool already_mapped = false;
  while (buffer >> line) {
    if(line == "Time:"){}
    else if(line == "Distance:"){
      reading_time = false;
    }
    else {
      if(reading_time){
        time.emplace_back(stoll(line));
      }
      else {
        distance.emplace_back(stoll(line));
      }
    }
  }

  int64_t anwser = calculateOutput(time,distance );
  return anwser;
}
int64_t generateNumber(vector<int64_t>& val){
  int64_t anwser ;;
   std::stringstream ss;
   std::copy(val.begin(), val.end(),std::ostream_iterator<int64_t>(ss));
   ss >> anwser;
   cout << anwser << endl;
   return anwser;
}
int part2() {
  std::stringstream buffer;
  read_from_file("/home/mateusz/AdventOfCode2023/Day06/input.txt", buffer);
  vector<int64_t> time;
  vector<int64_t> distance;

  string line;
  bool reading_time = true;
  bool already_mapped = false;
  while (buffer >> line) {
    if(line == "Time:"){}
    else if(line == "Distance:"){
      reading_time = false;
    }
    else {
      if(reading_time){
        time.emplace_back(stoll(line));
      }
      else {
        distance.emplace_back(stoll(line));
      }
    }
  }
  int64_t  t = generateNumber(time);
  int64_t d = generateNumber(distance);
  time.clear();
  time.emplace_back(t);
  distance.clear();
  distance.emplace_back(d);
  int64_t anwser = calculateOutput(time,distance );
  return anwser;
}

  
int main() {
  cout << part1() << endl;
  cout << part2() << endl;
}