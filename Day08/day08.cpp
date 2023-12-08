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

int part1() {
  std::stringstream buffer;
  read_from_file("/home/mateusz/AdventOfCode2023/Day08/input.txt", buffer);
  string navigation_lookup_table, key, equal, left, right;
  map<string, pair<string, string>> mapper;
  buffer >> navigation_lookup_table;
  pair<string, string> tmp;
  while (buffer >> key >> equal >> left >> right) {
    tmp = make_pair(left.substr(1, left.size() - 2),
                    right.substr(0, right.size() - 1));
    mapper.emplace(key, tmp);
  }
  int step = 0;
  string current = "AAA";
  while (true) {
    tmp = mapper[current];
    if (navigation_lookup_table[step % (navigation_lookup_table.length())] ==
        'L') {
      current = tmp.first;
    } else {
      current = tmp.second;
    }

    if (current == "ZZZ") {
      return step + 1;
    }
    step++;
  }

  return -1;
}

int64_t part2() {
  std::stringstream buffer;
  read_from_file("/home/mateusz/AdventOfCode2023/Day08/input.txt", buffer);
  string navigation_lookup_table, key, equal, left, right;
  map<string, pair<string, string>> mapper;
  buffer >> navigation_lookup_table;
  pair<string, string> tmp;
  vector<string> ending_with_A;
  while (buffer >> key >> equal >> left >> right) {
    tmp = make_pair(left.substr(1, left.size() - 2),
                    right.substr(0, right.size() - 1));
    mapper.emplace(key, tmp);
  }
  for (const auto& x : mapper) {
    if (x.first[2] == 'A') {
      ending_with_A.emplace_back(x.first);
    }
  }


  int64_t step = 1;
  vector<int64_t> how_many_steps;

  for (string& word : ending_with_A) {
    int64_t j = 0;
    while (word[2] != 'Z') {
      if (navigation_lookup_table[j % navigation_lookup_table.size()] == 'L') {
        word = mapper[word].first;
      } else {
        word = mapper[word].second;
      }
      j++;
    }
    how_many_steps.push_back(j);
  }
  for (const int& steps : how_many_steps) {
    step = lcm(steps, step);
  }

  return step;
}
int main() {
  cout << part1() << endl;
  cout << part2() << endl;
}