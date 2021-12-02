//
// Created by Nevin Zheng on 12/1/21.
//
#include <fstream>
#include <sstream>

#include <fmt/format.h>
#include <catch2/catch.hpp>

using namespace std;

enum class Direction { kForward, kDown, kUp };

struct Command {
  Direction dir;
  int distance;
};

std::pair<int, int> dive(const vector<Command> &commands) {
  int width{0};
  int depth{0};
  for (const auto &com : commands) {
    switch (com.dir) {
      case Direction::kForward:
        width += com.distance;
        break;
      case Direction::kDown:
        depth += com.distance;
        break;
      case Direction::kUp:
        depth -= com.distance;
        break;
    }
  }
  return {width, depth};
}

std::pair<int, int> dive2(const vector<Command> &commands) {
  int width{0};
  int depth{0};
  int aim{0};
  for (const auto &[dir, dist] : commands) {
    switch (dir) {
      case Direction::kForward:
        width += dist;
        depth += (aim * dist);
        break;
      case Direction::kDown:
        aim += dist;
        break;
      case Direction::kUp:
        aim -= dist;
        break;
    }
  }
  return {width, depth};
}

vector<Command> readFile() {
  auto infile = "TODO"
  std::ifstream in(infile);
  std::vector<Command> com;
  string dir;
  int dist{0};

  for (std::string line; std::getline(in, line);) {
    stringstream ss(line);
    ss >> dir >> dist;
    //    fmt::print("{}, {}\n", dir, dist);
    Direction parsed;
    if (dir == "down") {
      parsed = Direction::kDown;
    } else if (dir == "up") {
      parsed = Direction::kUp;
    } else {
      parsed = Direction::kForward;
    }
    com.push_back(Command{parsed, dist});
  }
  return com;
}

TEST_CASE("2_p1_example1", "[2_p1_1]") {
  auto commands = readFile();
  auto [x, y] = dive(commands);
  fmt::print("{}", x * y);
}

TEST_CASE("2_p2_example1", "[2_p2_1]") {
  auto commands = readFile();
  auto [x, y] = dive2(commands);
  fmt::print(" {}*{}= {}", x, y, x * y);
}