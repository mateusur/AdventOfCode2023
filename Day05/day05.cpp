#include <algorithm>
#include <fstream>
#include <iostream>
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

void calculateOutput(vector<long long>& seeds_numbers,
                     const vector<long long>& map_numbers) {
  for (long long& seed : seeds_numbers) {
    for (int i = 0; i < map_numbers.size(); i += 3) {
      if (seed >= map_numbers[i + 1] &&
          seed <= map_numbers[i + 1] + map_numbers[i + 2]) {
        int diff = seed - map_numbers[i + 1];
        seed = map_numbers[i] + diff;
        break;
      }
    }
  }
}

int part1() {
  std::stringstream buffer;
  read_from_file("/home/mateusz/AdventOfCode2023/Day05/input.txt", buffer);
  vector<long long> seeds_numbers;
  vector<long long> map_numbers;

  string line;
  enum mapping {
    seeds,
    seedToSoil,
    soilToFertilizer,
    fertilizerToWater,
    waterToLight,
    lightToTemperature,
    temperatureToHumidity,
    humidityToLocation
  };
  bool already_mapped = false;
  mapping map = seeds;
  while (buffer >> line) {
    if (line == "seeds:") {
      map = seeds;
    } else if (line == "seed-to-soil") {
      map = seedToSoil;

    } else if (line == "soil-to-fertilizer") {
      map = soilToFertilizer;
      already_mapped = false;
    } else if (line == "fertilizer-to-water") {
      map = fertilizerToWater;
      already_mapped = false;

    } else if (line == "water-to-light") {
      map = waterToLight;
      already_mapped = false;

    } else if (line == "light-to-temperature") {
      map = lightToTemperature;
      already_mapped = false;

    } else if (line == "temperature-to-humidity") {
      map = temperatureToHumidity;
      already_mapped = false;

    } else if (line == "humidity-to-location") {
      map = humidityToLocation;
      already_mapped = false;

    } else if (line == "map:") {
    } else {
      switch (map) {
        case seeds:
          seeds_numbers.emplace_back(stoll(line));
          break;
        case seedToSoil:
          map_numbers.emplace_back(stoll(line));
          break;
        case soilToFertilizer:
          if (!already_mapped) {
            calculateOutput(seeds_numbers, map_numbers);
            map_numbers.clear();
            already_mapped = true;
          }
          map_numbers.emplace_back(stoll(line));
          break;
        case fertilizerToWater:
          if (!already_mapped) {
            calculateOutput(seeds_numbers, map_numbers);
            map_numbers.clear();
            already_mapped = true;
          }
          map_numbers.emplace_back(stoll(line));

          break;
        case waterToLight:
          if (!already_mapped) {
            calculateOutput(seeds_numbers, map_numbers);
            map_numbers.clear();
            already_mapped = true;
          }
          map_numbers.emplace_back(stoll(line));

          break;
        case lightToTemperature:
          if (!already_mapped) {
            calculateOutput(seeds_numbers, map_numbers);
            map_numbers.clear();
            already_mapped = true;
          }
          map_numbers.emplace_back(stoll(line));

          break;
        case temperatureToHumidity:
          if (!already_mapped) {
            calculateOutput(seeds_numbers, map_numbers);
            map_numbers.clear();
            already_mapped = true;
          }
          map_numbers.emplace_back(stoll(line));

          break;
        case humidityToLocation:
          if (!already_mapped) {
            calculateOutput(seeds_numbers, map_numbers);
            map_numbers.clear();
            already_mapped = true;
          }
          map_numbers.emplace_back(stoll(line));

          break;
      }
    }
  }
  calculateOutput(seeds_numbers, map_numbers);
  long long anwser = *min_element(seeds_numbers.begin(), seeds_numbers.end());
  return anwser;
}

void calculateOutput(long long& seed, const vector<long long>& map_numbers) {
  for (int i = 0; i < map_numbers.size(); i += 3) {
    if (seed >= map_numbers[i + 1] &&
        seed < map_numbers[i + 1] + map_numbers[i + 2]) {
      seed = map_numbers[i] + (seed - map_numbers[i + 1]);
      break;
    }
  }
}
long long part2() {
  std::stringstream buffer;
  read_from_file("/home/mateusz/AdventOfCode2023/Day05/input.txt", buffer);
  vector<long long> seeds_numbers;
  vector<long long> vseedToSoil;
  vector<long long> vsoilToFertilizer;
  vector<long long> vfertilizerToWater;
  vector<long long> vwaterToLight;
  vector<long long> vlightToTemperature;
  vector<long long> vtemperatureToHumidity;
  vector<long long> vhumidityToLocation;
  long long smallest = INT64_MAX;
  string line;
  enum mapping {
    seeds,
    seedToSoil,
    soilToFertilizer,
    fertilizerToWater,
    waterToLight,
    lightToTemperature,
    temperatureToHumidity,
    humidityToLocation
  };
  mapping map = seeds;
  while (buffer >> line) {
    if (line == "seeds:") {
      map = seeds;
    } else if (line == "seed-to-soil") {
      map = seedToSoil;
    } else if (line == "soil-to-fertilizer") {
      map = soilToFertilizer;
    } else if (line == "fertilizer-to-water") {
      map = fertilizerToWater;
    } else if (line == "water-to-light") {
      map = waterToLight;
    } else if (line == "light-to-temperature") {
      map = lightToTemperature;
    } else if (line == "temperature-to-humidity") {
      map = temperatureToHumidity;
    } else if (line == "humidity-to-location") {
      map = humidityToLocation;
    } else if (line == "map:") {
    } else {
      switch (map) {
        case seeds:
          seeds_numbers.emplace_back(stoll(line));
          break;
        case seedToSoil:
          vseedToSoil.emplace_back(stoll(line));
          break;
        case soilToFertilizer:
          vsoilToFertilizer.emplace_back(stoll(line));
          break;
        case fertilizerToWater:
          vfertilizerToWater.emplace_back(stoll(line));
          break;
        case waterToLight:
          vwaterToLight.emplace_back(stoll(line));
          break;
        case lightToTemperature:
          vlightToTemperature.emplace_back(stoll(line));
          break;
        case temperatureToHumidity:
          vtemperatureToHumidity.emplace_back(stoll(line));
          break;
        case humidityToLocation:
          vhumidityToLocation.emplace_back(stoll(line));
          break;
      }
    }
  }
  for (int i = 0; i < seeds_numbers.size(); i += 2) {
    for (long long seed = seeds_numbers[i];
         seed < seeds_numbers[i] + seeds_numbers[i + 1]; ++seed) {
      long long seed_start = seed;
      calculateOutput(seed_start, vseedToSoil);
      calculateOutput(seed_start, vsoilToFertilizer);
      calculateOutput(seed_start, vfertilizerToWater);
      calculateOutput(seed_start, vwaterToLight);
      calculateOutput(seed_start, vlightToTemperature);
      calculateOutput(seed_start, vtemperatureToHumidity);
      calculateOutput(seed_start, vhumidityToLocation);
      if (seed_start < smallest) {
        smallest = seed_start;
      }
    }
  }
  return smallest;
}
int main() {
  // cout << part1() << endl;
  cout << part2() << endl;
}