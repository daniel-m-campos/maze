#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using std::abs;
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

enum class State { kEmpty, kObstacle, kClosed };

vector<State> ParseLine(const string& line) {
  istringstream line_stream(line);
  int n;
  char c;
  vector<State> row;
  while (line_stream >> n >> c && c == ',') {
    if (n == 0) {
      row.push_back(State::kEmpty);
    } else {
      row.push_back(State::kObstacle);
    }
  }
  return row;
}

vector<vector<State>> ReadBoardFile(const string& path) {
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

bool Compare(vector<int> a, vector<int> b) {
  // FIXME: use a struct here
  return a[2] + a[3] > b[2] + b[3];
}

int Heuristic(int x1, int y1, int x2, int y2) {
  return abs(x2 - x1) + abs(y2 - y1);
}

void AddToOpen(int x, int y, int g, int h, vector<vector<int>>& open_nodes,
               vector<vector<State>>& grid) {
  open_nodes.push_back(vector<int>{x, y, g, h});
  grid[x][y] = State::kClosed;
}

vector<vector<State>> Search(vector<vector<State>>& grid, const int init[2],
                             const int goal[2]) {
  auto x1 = init[0];
  auto y1 = init[1];
  auto x2 = goal[0];
  auto y2 = goal[1];
  auto g = 0;
  auto h = Heuristic(x1, y1, x2, y2);
  vector<vector<int>> open_nodes;

  AddToOpen(x1, y1, g, h, open_nodes, grid);
  cout << "No path found!" << '\n';
  return vector<vector<State>>{};
}

string CellString(State cell) {
  switch (cell) {
    case State::kObstacle:
      return "⛰️   ";
    default:
      return "0   ";
  }
}

void PrintBoard(const vector<vector<State>>& board) {
  for (const auto& i : board) {
    for (auto j : i) {
      cout << CellString(j);
    }
    cout << "\n";
  }
}

#include "test.cpp"

int main() {
  int init[2]{0, 0};
  int goal[2]{4, 5};
  auto board = ReadBoardFile("../1.board");
  auto solution = Search(board, init, goal);
  PrintBoard(solution);
  // Tests
  TestHeuristic();
  TestAddToOpen();
  TestCompare();
}