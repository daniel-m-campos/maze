#include "path_finder.h"

#include <algorithm>
#include <iostream>

#include "grid.h"

PathFinder::PathFinder() {
  original_grid_ = Grid();
  grid_ = original_grid_;
  open_ = std::vector<Cell>();
}

PathFinder::PathFinder(Grid grid) {
  original_grid_ = grid;
  grid_ = original_grid_;
  open_ = std::vector<Cell>();
}

int PathFinder::Heuristic(const Location &p1, const Location &p2) {
  return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

void PathFinder::AddToOpen(Cell cell) {
  open_.push_back(cell);
  grid_.Close(cell.location);
}

void PathFinder::ExpandNeighbors(const Cell &current, const Location &goal) {
  for (auto const [dx, dy] : deltas_) {
    Location adjacent{current.location.x + dx, current.location.y + dy};
    if (grid_.IsValid(adjacent)) {
      auto h2 = Heuristic(adjacent, goal);
      AddToOpen(Cell{adjacent, current.g + 1, h2});
    }
  }
}

bool PathFinder::Compare(const Cell &a, const Cell &b) {
  return a.g + a.h > b.g + b.h;
}

void PathFinder::CellSort(std::vector<Cell> *v) {
  std::sort(v->begin(), v->end(), Compare);
}

Cell PathFinder::Current() {
  CellSort(&open_);
  auto next = open_.back();
  open_.pop_back();
  return next;
}

Grid PathFinder::Search(const Location &start, const Location &goal) {
  grid_ = original_grid_;
  open_ = std::vector<Cell>();
  AddToOpen(Cell{start, 0, Heuristic(start, goal)});
  while (!open_.empty()) {
    Cell current = Current();
    grid_.SetAsPath(current.location);
    if (current.location == goal) {
      grid_.SetGoal(start, goal);
      std::cout << "🤖 Found a path!\n";
      return grid_;
    }
    ExpandNeighbors(current, goal);
  }
  std::cout << "No path found... 💩\n";
  return Grid();
}

std::vector<Cell> &PathFinder::GetOpenNodes() { return open_; }

Grid &PathFinder::GetGrid() { return grid_; }
