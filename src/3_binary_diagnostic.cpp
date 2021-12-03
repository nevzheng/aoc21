#include <fstream>
#include <sstream>

#include <fmt/format.h>
#include <catch2/catch.hpp>

#include <cstdint>

using namespace std;

std::pair<int, int> diagnose(const std::vector<string> &data) {
  auto bitwidth = data.front().size();
  std::vector<int> ones(bitwidth, 0);
  std::vector<int> zeros(bitwidth, 0);
  std::string eps_str(bitwidth, '0');
  std::string gam_str(bitwidth, '0');
  for (const auto &line : data) {
    for (auto i = 0UL; i < bitwidth; ++i) {
      line[i] == '0' ? ++zeros[i] : ++ones[i];
    }
  }
  for (auto i = 0UL; i < bitwidth; ++i) {
    if (ones[i] > zeros[i]) {
      eps_str[i] = '1';
      gam_str[i] = '0';
    } else {
      eps_str[i] = '0';
      gam_str[i] = '1';
    }
  }
  return {std::stoi(eps_str, 0, 2), std::stoi(gam_str, 0, 2)};
}

int diagnoseO2(const std::vector<string> &data) {
  auto current = data;
  auto pos = 0;
  while (current.size() != 1) {
    std::vector<string> ones;
    std::vector<string> zeros;
    for (const auto &item : current) {
      item.at(pos) == '0' ? zeros.push_back(item) : ones.push_back(item);
    }
    //    fmt::print("cur {}\n", fmt::join(current, ", "));
    //    fmt::print("pos: {}\n", pos);
    //    fmt::print("ones {}\n", fmt::join(ones, ", "));
    //    fmt::print("zeros {}\n\n", fmt::join(zeros, ", "));

    current = ones.size() >= zeros.size() ? ones : zeros;
    ++pos;
  }
  auto o2 = std::stoi(current.front(), nullptr, 2);
  return o2;
}

int diagnoseCO2(const std::vector<string> &data) {
  auto current = data;
  auto pos = 0;
  while (current.size() != 1) {
    std::vector<string> ones;
    std::vector<string> zeros;
    for (const auto &item : current) {
      item.at(pos) == '0' ? zeros.push_back(item) : ones.push_back(item);
    }
    //    fmt::print("cur {}\n", fmt::join(current, ", "));
    //    fmt::print("pos: {}\n", pos);
    //    fmt::print("ones {}\n", fmt::join(ones, ", "));
    //    fmt::print("zeros {}\n\n", fmt::join(zeros, ", "));

    current = zeros.size() <= ones.size() ? zeros : ones;
    ++pos;
  }
  auto o2 = std::stoi(current.front(), nullptr, 2);
  return o2;
}

vector<std::string> readFile() {
  auto infile = "/Users/nzheng/projects/aoc21/input/3a.txt"s;
  //  auto infile = "/Users/nzheng/projects/aoc21/input/3b.txt"s;
  std::ifstream in(infile);
  std::vector<string> com;
  for (std::string line; std::getline(in, line);) {
    com.push_back(line);
  }
  return com;
}

TEST_CASE("3_p1_example1", "[3_p1_1]") {
  auto data = readFile();
  auto [eps, gam] = diagnose(data);
  fmt::print("{} * {} = {}", eps, gam, eps * gam);
}

TEST_CASE("3_p2_example1", "[3_p2_1]") {
  auto data = readFile();
  auto o2 = diagnoseO2(data);
  auto co2 = diagnoseCO2(data);
  fmt::print("{} * {} = {}", o2, co2, o2 * co2);
}
