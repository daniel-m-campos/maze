#ifndef MAZE__PATH_FINDER_H_
#define MAZE__PATH_FINDER_H_

#include <vector>

#include "grid.h"

class PathFinder {
 public:
  PathFinder();
  explicit PathFinder(Grid grid);
  void AddToOpen(Cell node);
  void ExpandNeighbors(const Cell &current, const Location &goal);
  static int Heuristic(const Location &p1, const Location &p2);
  static bool Compare(const Cell &a, const Cell &b);
  static void CellSort(std::vector<Cell> *v);
  Cell Current();
  Grid Search(const Location &start, const Location &goal);
  std::vector<Cell> &GetOpenNodes();
  Grid &GetGrid();

 private:
  std::vector<Cell> open_;
  Grid original_grid_;
  Grid grid_;
  const int deltas_[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
};

#endif  // MAZE__PATH_FINDER_H_
