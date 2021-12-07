#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <fmt/format.h>
#include <catch2/catch.hpp>

using Point = std::pair<int, int>;
using Segment = std::pair<Point, Point>;

std::ostream &operator<<(std::ostream &os, const Segment &s) {
  auto str = fmt::format("({}, {}) -> ({}, {})", s.first.first, s.first.second, s.second.first, s.second.second);
  os << str;
  return os;
}

int venture1(std::vector<Segment> &segments) {
  auto max_x{0};
  auto max_y{0};
  for (auto &s : segments) {
    max_x = std::max(max_x, s.first.first);
    max_x = std::max(max_x, s.second.first);
    max_y = std::max(max_y, s.first.second);
    max_y = std::max(max_y, s.second.second);
  }
  std::vector<std::vector<int>> grid(max_x + 1, std::vector<int>(max_y + 1));

  for (const auto &s : segments) {
    // Consider only vertical and horizontal lines where  x1=x2 or y1=y2 for segment x1,y1 -> x2,y2
    //    std::cout << "Painting: " << s << '\n';
    if (s.first.first == s.second.first) {  // Vertical Line
      auto start = std::min(s.first.second, s.second.second);
      auto end = std::max(s.first.second, s.second.second);
      for (auto i = start; i <= end; ++i) {
        //        std::cout << '\t' << fmt::format("({}, {})\n", s.first.first, i);
        ++grid[s.first.first][i];
      }
    } else if (s.first.second == s.second.second) {  // Horizontal line
      auto start = std::min(s.first.first, s.second.first);
      auto end = std::max(s.first.first, s.second.first);
      for (auto i = start; i <= end; ++i) {
        //        std::cout << '\t' << fmt::format("({}, {})\n", i, s.first.second);
        ++grid[i][s.first.second];
      }
    }
  }

  auto ans = 0;
  for (auto i = 0; i <= max_x; i++) {
    for (auto j = 0; j <= max_y; j++) {
      if (grid[i][j] >= 2) {
        ++ans;
      }
    }
  }
  return ans;
}

int venture2(std::vector<Segment> &segments) {
  auto max_x{0};
  auto max_y{0};
  for (auto &s : segments) {
    max_x = std::max(max_x, s.first.first);
    max_x = std::max(max_x, s.second.first);
    max_y = std::max(max_y, s.first.second);
    max_y = std::max(max_y, s.second.second);
  }
  std::vector<std::vector<int>> grid(max_x + 1, std::vector<int>(max_y + 1));

  for (const auto &s : segments) {
    // Consider only vertical and horizontal lines where  x1=x2 or y1=y2 for segment x1,y1 -> x2,y2
    //    std::cout << "Painting: " << s << '\n';
    if (s.first.first == s.second.first) {  // Vertical Line
      auto start = std::min(s.first.second, s.second.second);
      auto end = std::max(s.first.second, s.second.second);
      for (auto i = start; i <= end; ++i) {
        //        std::cout << '\t' << fmt::format("({}, {})\n", s.first.first, i);
        ++grid[s.first.first][i];
      }
    } else if (s.first.second == s.second.second) {  // Horizontal line
      auto start = std::min(s.first.first, s.second.first);
      auto end = std::max(s.first.first, s.second.first);
      for (auto i = start; i <= end; ++i) {
        //        std::cout << '\t' << fmt::format("({}, {})\n", i, s.first.second);
        ++grid[i][s.first.second];
      }
    } else {  // 45 degree line
      auto cur = s.first;
      auto dx = (s.second.first - s.first.first) > 0 ? 1 : -1;
      auto dy = (s.second.second - s.first.second) > 0 ? 1 : -1;

      std::cout << s << '\n';
      std::cout << fmt::format("dx: {}, dy: {}\n", dx, dy);
      while (cur != s.second) {
        //        std::cout << cur.first << ", "<< cur.second << '\n';
        ++grid[cur.first][cur.second];
        cur.first += dx;
        cur.second += dy;
      }
      ++grid[cur.first][cur.second];
    }
  }

  auto ans = 0;
  for (auto i = 0; i < max_x + 1; i++) {
    for (auto j = 0; j < max_y + 1; j++) {
      if (grid[i][j] >= 2) {
        ++ans;
      }
    }
  }
  return ans;
}

/**
 * readFile parses the input into a vector of Segments
 * Sample Line: 0,9 -> 5,9
 * @param filepath
 * @return
 */
std::vector<Segment> readFile(std::string filepath) {
  std::fstream f_st(filepath);
  std::string line;
  std::vector<Segment> segments;
  while (std::getline(f_st, line)) {
    int a1 = 0;
    int a2 = 0;
    int b1 = 0;
    int b2 = 0;
    std::sscanf(line.c_str(), "%d,%d -> %d, %d", &a1, &a2, &b1, &b2);
    segments.push_back({{a1, a2}, {b1, b2}});
  }
  return segments;
}

TEST_CASE("5_p1_example1", "[5_p1_1]") {
  auto input = "/Users/nzheng/projects/aoc21/input/5a.txt";
  auto segments = readFile(input);
  const int expected = 5;
  auto result = venture1(segments);
  REQUIRE(result == expected);
}

TEST_CASE("5_p1_example2", "[5_p1_2]") {
  auto input = "/Users/nzheng/projects/aoc21/input/5b.txt";
  auto segments = readFile(input);
  const int expected = 7644;
  auto result = venture1(segments);
  REQUIRE(result == expected);
}

TEST_CASE("5_p2_example1", "[5_p2_1]") {
  auto input = "/Users/nzheng/projects/aoc21/input/5a.txt";
  auto segments = readFile(input);
  const int expected = 12;
  auto result = venture2(segments);
  REQUIRE(result == expected);
}

TEST_CASE("5_p2_example2", "[5_p2_1]") {
  auto input = "/Users/nzheng/projects/aoc21/input/5b.txt";
  auto segments = readFile(input);
  const int expected = 18627;
  auto result = venture2(segments);
  REQUIRE(result == expected);
}