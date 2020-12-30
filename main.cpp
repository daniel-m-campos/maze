#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

enum class State { kEmpty, kObstacle };

vector<State> ParseLine(const string &line) {
  istringstream sline(line);
  int n;
  char c;
  vector<State> row;
  while (sline >> n >> c && c == ',') {
    if (n == 0) {
      row.push_back(State::kEmpty);
    } else {
      row.push_back(State::kObstacle);
    }
  }
  return row;
}

vector<vector<State>> ReadBoardFile(const string &path) {
  ifstream my_file(path);
  vector<vector<State>> board{};
  if (my_file) {
    string line;
    while (getline(my_file, line)) {
      vector<State> row = ParseLine(line);
      board.push_back(row);
    }
  }
  return board;
}

string CellString(State cell) {
  switch (cell) {
    case State::kObstacle:
      return "⛰️   ";
    default:
      return "0   ";
  }
}

void PrintBoard(const vector<vector<State>> &board) {
  for (const auto &i : board) {
    for (auto j : i) {
      cout << CellString(j);
    }
    cout << "\n";
  }
}

int main() {
  auto board = ReadBoardFile("../1.board");
  PrintBoard(board);
}