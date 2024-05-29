#ifndef MAZE__GRID_H_
#define MAZE__GRID_H_
#include <string>
#include <vector>

enum class State { kEmpty, kObstacle, kClosed, kPath, kStart, kFinish };

struct Location {
  int x;
  int y;
  bool operator==(const Location& other) const {
    return x == other.x && y == other.y;
  }
};

struct Cell {
  Location location{};
  int g{0};
  int h{};
  bool operator==(const Cell& other) const {
    return location == other.location && g == other.g && h == other.h;
  }
};

class Grid {
 public:
  Grid() { grid_ = std::vector<std::vector<State>>{}; };
  explicit Grid(const std::string& path);
  explicit Grid(const std::vector<std::vector<State>>& grid);
  State GetState(const Location& location);
  bool IsEmpty(const Location& location);
  void SetAsPath(const Location& location);
  void SetGoal(const Location& start, const Location& finish);
  void Close(const Location& location);
  bool IsValid(const Location& location);
  int NumRows() const { return grid_.size(); };
  int NumColumns() const { return grid_[0].size(); };
  static std::string CellString(State cell);
  void Print();
  bool operator==(const Grid& other) const;

 private:
  std::vector<std::vector<State>> grid_;
  static std::vector<State> ParseLine(const std::string& line);
  static std::vector<std::vector<State>> ReadBoardFile(const std::string& path);
};

#endif  // MAZE__GRID_H_
