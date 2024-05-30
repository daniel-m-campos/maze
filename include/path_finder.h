#ifndef MAZE__PATH_FINDER_H_
#define MAZE__PATH_FINDER_H_

#include <queue>
#include <vector>

#include "grid.h"

struct CompareCells {
  bool operator()(const Cell &a, const Cell &b) const {
    int f1 = a.g + a.h, f2 = b.g + b.h;
    if (f1 == f2) {
      return a.h > b.h;
    }
    return f1 > f2;
  }
};

using CellQueue = std::priority_queue<Cell, std::vector<Cell>, CompareCells>;

class PathFinder {
public:
  PathFinder();
  explicit PathFinder(Grid grid);
  void open(Cell node);
  void expandNeighbors(const Cell &current, const Location &goal);
  static int heuristic(const Location &p1, const Location &p2);
  static void sort(std::vector<Cell> *v);
  Cell next();
  Grid search(const Location &start, const Location &goal);
  CellQueue &getOpen();
  Grid &getGrid();

private:
  CellQueue open_;
  Grid grid_;
  Grid original_grid_;
  const int deltas_[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
};

#endif // MAZE__PATH_FINDER_H_
