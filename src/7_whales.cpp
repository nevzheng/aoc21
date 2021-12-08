#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include <fmt/format.h>
#include <catch2/catch.hpp>

int whales1(std::vector<int> &crabs) {
  std::sort(crabs.begin(), crabs.end());
  auto minCrab = crabs.front();
  auto maxCrab = crabs.back();

  auto bestFit = -1;
  auto bestFitSum = INT_MAX;

  for (auto i = minCrab; i < maxCrab; ++i) {
    auto curSum = 0;
    for (auto crab : crabs) {
      curSum += crab >= i ? (crab - i) : (i - crab);
    }

    if (curSum < bestFitSum) {
      bestFit = i;
      bestFitSum = curSum;
    }
  }
  auto netCost = 0;
  for (auto crab : crabs) {
    netCost += abs(crab - bestFit);
  }
  return netCost;
}

int whales2(std::vector<int> &crabs) {
  std::sort(crabs.begin(), crabs.end());
  auto minCrab = crabs.front();
  auto maxCrab = crabs.back();

  auto bestFitSum = INT_MAX;

  for (auto i = minCrab; i <= maxCrab; ++i) {
    auto curSum = 0;
    for (auto crab : crabs) {
      auto dist = crab >= i ? (crab - i) : (i - crab);
      curSum += ((dist) * (dist + 1)) / 2;
    }
    if (curSum < bestFitSum) {
      bestFitSum = curSum;
    }
  }
  return bestFitSum;
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

TEST_CASE("7_p1_example1", "[7_p1_1]") {
  auto input = "/Users/nzheng/projects/aoc21/input/7a.txt";
  auto crabs = readFile(input);
  auto result = whales1(crabs);
  auto expected = 37;
  REQUIRE(result == expected);
}

TEST_CASE("7_p1_example2", "[7_p1_2]") {
  auto input = "/Users/nzheng/projects/aoc21/input/7b.txt";
  auto crabs = readFile(input);
  auto result = whales1(crabs);
  auto expected = 359648;
  REQUIRE(result == expected);
}

TEST_CASE("7_p2_example1", "[7_p2_1]") {
  auto input = "/Users/nzheng/projects/aoc21/input/7a.txt";
  auto crabs = readFile(input);
  auto result = whales2(crabs);
  auto expected = 168;
  REQUIRE(result == expected);
}

TEST_CASE("7_p2_example2", "[7_p2_2]") {
  auto input = "/Users/nzheng/projects/aoc21/input/7b.txt";
  auto crabs = readFile(input);
  auto result = whales2(crabs);
  auto expected = 100727924;
  REQUIRE(result == expected);
}