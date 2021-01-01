#ifndef MAZE__GRID_H_
#define MAZE__GRID_H_
#include <string>
#include <vector>

enum class State { kEmpty, kObstacle, kClosed, kPath, kStart, kFinish };

struct Point {
  int x;
  int y;
  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
};

struct Node {
  Point point;
  int g = 0;
  int h;
};

class Grid {
 private:
  std::vector<std::vector<State>> grid_;
  static std::vector<State> ParseLine(const std::string& line);
  static std::vector<std::vector<State>> ReadBoardFile(const std::string& path);
 public:

  Grid() { grid_ = std::vector<std::vector<State>>{}; };
  explicit Grid(const std::string& path);
  Grid(const std::vector<std::vector<State>>& grid);
  State GetState(Point point);
  bool IsEmpty(Point point);
  void SetAsPath(Point point);
  void SetGoal(Point start, Point finish);
  void Close(Point point);
  bool CheckValidCell(Point point);
  int NumRows() { return grid_.size(); };
  int NumColumns() { return grid_[0].size(); };
  static std::string CellString(State cell);
  void Print();
};

#endif  // MAZE__GRID_H_
