#include "grid.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::vector<State> Grid::ParseLine(const std::string& line) {
  std::istringstream line_stream(line);
  int n;
  char c;
  std::vector<State> row;
  while (line_stream >> n >> c && c == ',') {
    if (n == 0) {
      row.push_back(State::kEmpty);
    } else {
      row.push_back(State::kObstacle);
    }
  }
  return row;
}

std::vector<std::vector<State>> Grid::ReadBoardFile(const std::string& path) {
  std::ifstream my_file(path);
  std::vector<std::vector<State>> board{};
  if (my_file) {
    std::string line;
    while (getline(my_file, line)) {
      std::vector<State> row = ParseLine(line);
      board.push_back(row);
    }
  }
  return board;
}

Grid::Grid(const std::vector<std::vector<State>>& grid) { grid_ = grid; }

Grid::Grid(const std::string& path) { grid_ = ReadBoardFile(path); }

State Grid::GetState(Point point) { return grid_[point.x][point.y]; }

void Grid::SetAsPath(Point point) { grid_[point.x][point.y] = State::kPath; }

bool Grid::IsEmpty(Point point) { return GetState(point) == State::kEmpty; }

void Grid::Close(Point point) { grid_[point.x][point.y] = State::kClosed; }

bool Grid::CheckValidCell(const Point point) {
  bool x_valid = point.x >= 0 && point.x < NumRows();
  bool y_valid = point.y >= 0 && point.y < NumColumns();
  return (x_valid && y_valid && IsEmpty(point));
}

std::string Grid::CellString(State cell) {
  switch (cell) {
    case State::kObstacle:
      return "⛰️   ";
    case State::kPath:
      return "🚗   ";
    case State::kFinish:
      return "🏁   ";
    case State::kStart:
      return "🚦   ";
    default:
      return "0   ";
  }
}

void Grid::Print() {
  for (const auto& i : grid_) {
    for (auto j : i) {
      std::cout << CellString(j);
    }
    std::cout << "\n";
  }
}

void Grid::SetGoal(Point start, Point finish) {
  grid_[start.x][start.y] = State::kStart;
  grid_[finish.x][finish.y] = State::kFinish;
}
