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

enum class State { kEmpty, kObstacle };

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

vector<vector<State>> Search(vector<vector<State>>& board, int first[],
                             int second[]) {
  cout << "No path found!" << '\n';
  vector<vector<State>> new_board;
  return new_board;
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

int main() {
  int init[]{0, 0};
  int goal[]{4, 5};
  auto board = ReadBoardFile("1.board");
  auto solution = Search(board, init, goal);
  PrintBoard(solution);
}
