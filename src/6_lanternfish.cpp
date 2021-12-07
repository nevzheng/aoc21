#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include <fmt/format.h>
#include <catch2/catch.hpp>

uint64_t lanternFish1(const std::vector<int> &fish, int max_day) {
  // track the reproduction periods of each fish
  std::map<int, uint64_t> buckets;
  // Sort the input into the buckets
  for (const auto &f : fish) {
    ++buckets[f];
  }

  for (auto day = 0; day < max_day; ++day) {
    if (buckets.contains(day)) {
      buckets[day + 7] += buckets[day];      // schedule original fish next spawn
      buckets[day + 7 + 2] += buckets[day];  // Spawn new fish
      buckets.erase(day);                    // remove old bucket
    }
  }

  auto ans = 0UL;
  for (auto &bucket : buckets) {
    ans += bucket.second;
  }
  return ans;
}

std::vector<int> readFile(std::string filepath) {
  std::fstream fst(filepath);
  std::vector<int> res;
  std::string tok;
  while (std::getline(fst, tok, ',')) {
    res.push_back(std::stoi(tok));
  }
  return res;
}

TEST_CASE("6_p1_example1", "[6_p1_1]") {
  auto input = "/Users/nzheng/projects/aoc21/input/6a.txt";
  auto segments = readFile(input);
  auto max_day = 80;
  auto result = lanternFish1(segments, max_day);
  auto expected = 5934UL;
  REQUIRE(result == expected);
}

TEST_CASE("6_p1_example2", "[6_p1_2]") {
  auto input = "/Users/nzheng/projects/aoc21/input/6b.txt";
  auto segments = readFile(input);
  auto max_day = 80;
  auto result = lanternFish1(segments, max_day);
  auto expected = 383160UL;
  REQUIRE(result == expected);
}

TEST_CASE("6_p2_example1", "[6_p2_1]") {
  auto input = "/Users/nzheng/projects/aoc21/input/6a.txt";
  auto segments = readFile(input);
  auto max_day = 256;
  auto result = lanternFish1(segments, max_day);
  auto expected = 26984457539UL;
  REQUIRE(result == expected);
}

TEST_CASE("6_p2_example2", "[6_p2_2]") {
  auto input = "/Users/nzheng/projects/aoc21/input/6b.txt";
  auto segments = readFile(input);
  auto max_day = 256;
  auto result = lanternFish1(segments, max_day);
  auto expected = 1721148811504UL;
  REQUIRE(result == expected);
}
