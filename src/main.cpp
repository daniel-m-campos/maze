#include <iostream>

#include "path_finder.h"

int main() {
  Point start{0, 0};
  Point goal{4, 5};
  Grid grid("1.board");
  std::cout << "======= The Grid! =========" << '\n';
  grid.Print();
  PathFinder path_finder(grid);
  std::cout << "======= Starting search! =========" << '\n';
  auto solution = path_finder.Search(start, goal);
  solution.Print();
  std::cout << "Done!";
}