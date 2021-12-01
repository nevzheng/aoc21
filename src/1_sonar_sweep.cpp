//
// Created by Nevin Zheng on 12/1/21.
//
#include <catch2/catch.hpp>

#include <fmt/format.h>

using namespace std;

void sonarSweep(){
  fmt::print("Hello World");
}

TEST_CASE("1_example1", "[1]") {
  sonarSweep();
}
