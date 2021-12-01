//
// Created by Nevin Zheng on 12/1/21.
//
#include <catch2/catch.hpp>

#include <fmt/format.h>
#include <fstream>

using namespace std;

int sonarSweep1(const std::vector<int> &sweep) {
  if (sweep.size() < 2) return 0;
  auto count = 0;
  for (auto i = 1UL; i < sweep.size(); ++i) {
    if (sweep[i - 1] < sweep[i]) ++count;
  }
  return count;
}

int sonarSweep2(const std::vector<int> &sweep) {
  const auto winLen = 3UL;

  if (sweep.size() < winLen) return 0;  // no prior value

  auto curSum = std::accumulate(begin(sweep), begin(sweep) + winLen, 0);  // sum of first window

  auto count = 0;
  for (auto nxt = winLen; nxt < sweep.size(); ++nxt) {
    auto nxtWin = curSum + sweep[nxt] - sweep[nxt - winLen];  // value of the next window
    if (curSum < nxtWin) ++count;                             // count if increasing
    curSum = nxtWin;                                          // set next win value
  }

  return count;
}

vector<int> readFile() {
  auto infile = "TODO";
  std::ifstream in(infile);
  int x{0};
  vector<int> v;
  while (in >> x) v.push_back(x);
  return v;
}

TEST_CASE("1_p1_example1", "[1_p1_1]") {
  const vector<int> input{199, 200, 208, 210, 200, 207, 240, 269, 260, 263};
  auto result = sonarSweep1(input);
  REQUIRE(result == 7);
}

TEST_CASE("1_p1_full", "[1_p1_2]") {
  auto v = readFile();
  auto result = sonarSweep1(v);
  fmt::print("answer is: {}", result);
}

TEST_CASE("1_p2_example2", "[1_p2_1]") {
  const vector<int> input{199, 200, 208, 210, 200, 207, 240, 269, 260, 263};
  auto result = sonarSweep2(input);
  REQUIRE(result == 5);
}

TEST_CASE("1_p2_full", "[1_p2_2]") {
  auto v = readFile();
  auto result = sonarSweep2(v);  // note(nlz): not sure why this is off by 1
  fmt::print("answer is: {}", result);
}
