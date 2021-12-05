#include <fstream>
#include <sstream>

#include <fmt/format.h>
#include <catch2/catch.hpp>

#include <cstdint>

typedef std::vector<std::vector<int>> Board;
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

std::pair<std::vector<int>, std::vector<Board>> readFile() {
  //  auto infile = "/Users/nzheng/projects/aoc21/input/4a.txt"s;
  auto infile = "/Users/nzheng/projects/aoc21/input/4b.txt"s;
  std::ifstream instream(infile);

  // Read the First line
  std::string bingocalls;
  std::getline(instream, bingocalls);
  std::string tok;

  std::vector<int> calls;
  std::istringstream callst(bingocalls);
  while (std::getline(callst, tok, ',')) {
    calls.push_back(stoi(tok));
  }

  std::vector<std::vector<string>> board_strings;
  std::vector<string> board_string;

  while (std::getline(instream, tok)) {  // Skips Header line
    for (auto i = 0; i < 5; ++i) {       // reads a board_string
      std::getline(instream, tok);
      board_string.push_back(tok);
    }
    board_strings.push_back(board_string);
    board_string.clear();
  }

  std::vector<Board> boards;

  Board current_board;
  for (auto board : board_strings) {
    for (auto line : board) {
      std::stringstream sst(line);
      std::vector<int> board_line;
      int x;
      while (sst >> x) {
        board_line.push_back(x);
      }
      current_board.push_back(board_line);
      board_line.clear();
    }
    boards.push_back(current_board);
    current_board.clear();
  }

  return {calls, boards};
}

constexpr int kMarked = -1;

bool checkBoard(const Board &board) {
  // Check Rows
  for (auto i = 0; i < 5; ++i) {
    if (std::all_of(begin(board[i]), end(board[i]), [](auto p) { return p == kMarked; })) {
      return true;
    }
  }
  // Check Columns
  for (auto i = 0; i < 5; ++i) {
    auto win = true;
    for (auto j = 0; j < 5; ++j) {
      win = win && (board[j][i] == kMarked);
    }
    if (win) {
      return true;
    }
  }
  return false;
}

int scoreBoard(const Board &board) {
  auto sum = 0;
  for (auto i = 0; i < 5; ++i) {
    for (auto j = 0; j < 5; ++j) {
      if (board[i][j] != kMarked) {
        sum += board[i][j];
      }
    }
  }
  return sum;
}

void markBoard(Board &board, int call) {
  for (auto i = 0; i < 5; ++i) {
    for (auto j = 0; j < 5; ++j) {
      if (board[i][j] == call) {
        board[i][j] = kMarked;
        return;
      }
    }
  }
}

int bingo1(std::vector<int> &calls, std::vector<Board> &boards) {
  for (auto call : calls) {
    for (auto i = 0UL; i < size(boards); ++i) {
      markBoard(boards[i], call);
      if (checkBoard(boards[i])) {
        return call * scoreBoard(boards[i]);
      }
    }
  }
  return -1;
}

void bingo2(std::vector<int> &calls, std::vector<Board> &boards) {
  for (auto call : calls) {
    vector<int> toRemove;
    fmt::print("{}\n", boards.size());
    for (auto i = 0UL; i < size(boards); ++i) {
      markBoard(boards[i], call);
      if (checkBoard(boards[i])) {
        toRemove.push_back(i);
        fmt::print("{}\n", call * scoreBoard(boards[i]));
      }
    }
    std::reverse(begin(toRemove), end(toRemove));
    for (auto i : toRemove) {
      boards.erase(begin(boards) + i);
    }
  }
}

TEST_CASE("4_p1_example1", "[4_p2_1]") {
  auto data = readFile();
  auto first_winning_score = bingo1(data.first, data.second);
  fmt::print("{}\n", first_winning_score);
}

TEST_CASE("4_p2_example1", "[4_p2_1]") {
  auto data = readFile();
  bingo2(data.first, data.second);
}
