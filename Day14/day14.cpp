#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
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
  read_from_file("/home/mateusz/AdventOfCode2023/Day14/input.txt", buffer);
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
void slide_rocks_north(vector<vector<char>> &all_numbers) {
  for (size_t col = 0; col < all_numbers[0].size(); ++col) {
    char k = 'z';
    for (size_t row = 0; row < all_numbers.size(); ++row) {
      char t = all_numbers[row][col];
      if (all_numbers[row][col] == '.') {
        size_t next_rock = row + 1;
        while (next_rock < all_numbers.size() &&
               all_numbers[next_rock][col] == '.') {
          next_rock++;
        }
        if (next_rock < all_numbers.size() &&
            all_numbers[next_rock][col] == '#') {
          row = next_rock;
        } else if (next_rock < all_numbers.size()) {
          all_numbers[row][col] = 'O';
          all_numbers[next_rock][col] = '.';
        }
      }
    }
  }
}
void slide_rocks_south(vector<vector<char>> &all_numbers) {
  for (size_t col = 0; col < all_numbers[0].size(); ++col) {
    char k = 'z';
    for (size_t row = all_numbers.size() - 1; row >= 1; --row) {
      char t = all_numbers[row][col];
      if (all_numbers[row][col] == '.') {
        size_t next_rock = row - 1;
        while (next_rock >= 1 && all_numbers[next_rock][col] == '.') {
          next_rock--;
        }
        char g = all_numbers[next_rock][col];
        if (next_rock >= 0 && all_numbers[next_rock][col] == '#') {
          row = next_rock;
        } else if (next_rock >= 0 && all_numbers[next_rock][col] == 'O') {
          all_numbers[row][col] = 'O';
          all_numbers[next_rock][col] = '.';
        }
        if (row == 0) {
          break;
        }
      }
    }
  }
}
void slide_rocks_west(vector<vector<char>> &all_numbers) {
  for (size_t row = 0; row < all_numbers.size(); ++row) {
    char k = 'z';
    for (size_t col = 0; col < all_numbers[0].size(); ++col) {
      char t = all_numbers[row][col];
      if (all_numbers[row][col] == '.') {
        size_t next_rock = col + 1;
        while (next_rock < all_numbers[0].size() &&
               all_numbers[row][next_rock] == '.') {
          next_rock++;
        }
        // char g=all_numbers[next_rock][col];
        if (next_rock < all_numbers[0].size() &&
            all_numbers[row][next_rock] == '#') {
          col = next_rock;
        } else if (next_rock < all_numbers[0].size() &&
                   all_numbers[row][next_rock] == 'O') {
          all_numbers[row][col] = 'O';
          all_numbers[row][next_rock] = '.';
        }
      }
    }
  }
}
void slide_rocks_east(vector<vector<char>> &all_numbers) {
  for (size_t row = 0; row < all_numbers.size(); ++row) {
    char k = 'z';
    for (size_t col = all_numbers[0].size() - 1; col >= 1; --col) {
      char t = all_numbers[row][col];
      if (all_numbers[row][col] == '.') {
        size_t next_rock = col - 1;
        while (next_rock > 0 && all_numbers[row][next_rock] == '.') {
          next_rock--;
        }
        // char g=all_numbers[next_rock][col];
        if (next_rock >= 0 && all_numbers[row][next_rock] == '#') {
          col = next_rock;
        } else if (next_rock >= 0 && all_numbers[row][next_rock] == 'O') {
          all_numbers[row][col] = 'O';
          all_numbers[row][next_rock] = '.';
        }
        if (col == 0) {
          break;
        }
      }
    }
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
int part1() {
  vector<vector<char>> all_numbers;
  read_elements(all_numbers);
  slide_rocks_north(all_numbers);
  return count_points(all_numbers);
}
int part2() {
  typedef vector<vector<char>> my2dChar;
  my2dChar all_numbers;
  read_elements(all_numbers); //
  map<my2dChar, int64_t> already_seen;
  int64_t iterations_to_do = 1000000000;
  bool found = false;
  for (int64_t counter = 0; counter < iterations_to_do; ++counter) {

    slide_rocks_north(all_numbers);
    slide_rocks_west(all_numbers);
    slide_rocks_south(all_numbers);
    slide_rocks_east(all_numbers);

    auto it = already_seen.insert({all_numbers, counter});
    if (it.second == false && !found) {
      int64_t tmp = iterations_to_do - counter;
      iterations_to_do = tmp % (counter - it.first->second);
      iterations_to_do += counter;
      found = true;
    }
  }
  return count_points(all_numbers);
}
int main() {
  // cout << part1() << endl;
  cout << part2() << endl;
}