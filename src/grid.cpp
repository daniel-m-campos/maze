#include "grid.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::vector<State> Grid::parseLine(const std::string &line) {
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

std::vector<std::vector<State>> Grid::readBoardFile(const std::string &path) {
  std::ifstream file(path);
  std::vector<std::vector<State>> board{};
  if (!file) {
    throw std::runtime_error("Could not open " + path);
  }
  std::string line;
  while (getline(file, line)) {
    std::vector<State> row = parseLine(line);
    board.push_back(row);
  }
  return board;
}

Grid::Grid(const std::vector<std::vector<State>> &grid) : grid_{grid} {}

Grid::Grid(const std::string &path) { grid_ = readBoardFile(path); }

State Grid::getState(const Location &location) const {
  return grid_[location.x][location.y];
}

void Grid::setToPath(const Location &location) {
  grid_[location.x][location.y] = State::kPath;
}

bool Grid::isEmpty(const Location &location) const {
  return getState(location) == State::kEmpty;
}

void Grid::setToClose(const Location &location) {
  grid_[location.x][location.y] = State::kClosed;
}

bool Grid::isValid(const Location &location) const {
  bool x_valid = location.x >= 0 && location.x < numRows();
  bool y_valid = location.y >= 0 && location.y < numColumns();
  return (x_valid && y_valid && isEmpty(location));
}

std::string Grid::ToString(State cell) {
  switch (cell) {
  case State::kObstacle:
    return "👾️  ";
  case State::kPath:
    return "🚀  ";
  case State::kFinish:
    return "🏁  ";
  case State::kStart:
    return "🚦  ";
  default:
    return "🌌  ";
  }
}

void Grid::print() const {
  for (const auto &i : grid_) {
    for (auto j : i) {
      std::cout << ToString(j);
    }
    std::cout << "\n";
  }
}

void Grid::setToGoal(const Location &start, const Location &finish) {
  grid_[start.x][start.y] = State::kStart;
  grid_[finish.x][finish.y] = State::kFinish;
}

bool Grid::operator==(const Grid &other) const { return grid_ == other.grid_; }
