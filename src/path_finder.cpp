#include "path_finder.h"

#include <algorithm>
#include <iostream>

#include "grid.h"

PathFinder::PathFinder() {
  original_grid_ = Grid();
  grid_ = original_grid_;
  open_ = std::vector<Node>();
}

PathFinder::PathFinder(Grid grid) {
  original_grid_ = grid;
  grid_ = original_grid_;
  open_ = std::vector<Node>();
}

int PathFinder::Heuristic(const Point &p1, const Point &p2) {
  return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

void PathFinder::AddToOpen(Node node) {
  open_.push_back(node);
  grid_.Close(node.point);
}

void PathFinder::ExpandNeighbors(const Node &current, const Point &goal) {
  for (auto [dx, dy] : deltas_) {
    Point adjacent{current.point.x + dx, current.point.y + dy};
    if (grid_.CheckValidCell(adjacent)) {
      auto h2 = Heuristic(adjacent, goal);
      AddToOpen(Node{adjacent, current.g + 1, h2});
    }
  }
}

bool PathFinder::Compare(Node a, Node b) { return a.g + a.h > b.g + b.h; }

void PathFinder::CellSort(std::vector<Node> *v) {
  std::sort(v->begin(), v->end(), Compare);
}

Node PathFinder::Current() {
  CellSort(&open_);
  auto next = open_.back();
  open_.pop_back();
  return next;
}

Grid PathFinder::Search(Point start, Point goal) {
  grid_ = original_grid_;
  open_ = std::vector<Node>();
  AddToOpen(Node{start, 0, Heuristic(start, goal)});
  while (!open_.empty()) {
    Node current = Current();
    grid_.SetAsPath(current.point);
    if (current.point == goal) {
      grid_.SetGoal(start, goal);
      return grid_;
    }
    ExpandNeighbors(current, goal);
  }
  std::cout << "No path found!" << '\n';
  return Grid();
}

std::vector<Node> &PathFinder::GetOpenNodes() { return open_; }

Grid &PathFinder::GetGrid() { return grid_; }
