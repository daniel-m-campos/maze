#include "path_finder.h"

#include <algorithm>
#include <iostream>

#include "grid.h"
#include <cassert>

PathFinder::PathFinder() : PathFinder(Grid()) {}

PathFinder::PathFinder(Grid grid)
    : open_(CompareCells()), grid_{grid}, original_grid_{grid} {}

int PathFinder::heuristic(const Location &p1, const Location &p2) {
  return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

void PathFinder::open(Cell cell) {
  open_.push(cell);
  grid_.setToClose(cell.location);
}

void PathFinder::expandNeighbors(const Cell &current, const Location &goal) {
  for (auto const [dx, dy] : deltas_) {
    Location adjacent{current.location.x + dx, current.location.y + dy};
    if (grid_.isValid(adjacent)) {
      auto h2 = heuristic(adjacent, goal);
      open(Cell{adjacent, current.g + 1, h2});
    }
  }
}

Cell PathFinder::next() {
  auto next = open_.top();
  open_.pop();
  return next;
}

Grid PathFinder::search(const Location &start, const Location &goal) {
  grid_ = original_grid_;
  assert(open_.empty() && "Open list should be empty!");
  open(Cell{start, 0, heuristic(start, goal)});
  while (!open_.empty()) {
    Cell current = next();
    grid_.setToPath(current.location);
    if (current.location == goal) {
      grid_.setToGoal(start, goal);
      std::cout << "🤖 Found a path!\n";
      return grid_;
    }
    expandNeighbors(current, goal);
  }
  std::cout << "No path found... 💩\n";
  return Grid();
}

CellQueue &PathFinder::getOpen() { return open_; }

Grid &PathFinder::getGrid() { return grid_; }
