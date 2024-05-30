#ifndef MAZE__GRID_H_
#define MAZE__GRID_H_
#include <string>
#include <vector>

enum class State { kEmpty, kObstacle, kClosed, kPath, kStart, kFinish };

struct Location {
  int x;
  int y;
  bool operator==(const Location &other) const {
    return x == other.x && y == other.y;
  }
};

struct Cell {
  Location location{};
  int g{0};
  int h{};
  bool operator==(const Cell &other) const {
    return location == other.location && g == other.g && h == other.h;
  }
};

class Grid {
public:
  Grid() {};
  explicit Grid(const std::string &path);
  explicit Grid(const std::vector<std::vector<State>> &grid);
  State getState(const Location &location) const;
  int numRows() const { return grid_.size(); };
  int numColumns() const { return grid_[0].size(); };
  bool isEmpty(const Location &location) const;
  bool isValid(const Location &location) const;
  void print() const;
  void setToPath(const Location &location);
  void setToGoal(const Location &start, const Location &finish);
  void setToClose(const Location &location);
  static std::string ToString(State cell);
  bool operator==(const Grid &other) const;

private:
  static std::vector<State> parseLine(const std::string &line);
  static std::vector<std::vector<State>> readBoardFile(const std::string &path);

private:
  std::vector<std::vector<State>> grid_;
};

#endif // MAZE__GRID_H_
