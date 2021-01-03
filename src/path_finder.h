#ifndef MAZE__PATH_FINDER_H_
#define MAZE__PATH_FINDER_H_

#include <vector>

#include "grid.h"

class PathFinder {
 private:
  std::vector<Node> open_;
  Grid original_grid_;
  Grid grid_;
  const int deltas_[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
 public:

  PathFinder();
  explicit PathFinder(Grid grid);
  void AddToOpen(Node node);
  void ExpandNeighbors(const Node &current, const Point &goal);
  static int Heuristic(const Point &p1, const Point &p2);
  static bool Compare(Node a, Node b);
  static void CellSort(std::vector<Node> *v);
  Node Current();
  Grid Search(Point start, Point goal);
  std::vector<Node> &GetOpenNodes();
  Grid &GetGrid();
};

#endif  // MAZE__PATH_FINDER_H_
