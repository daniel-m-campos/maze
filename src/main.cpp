#include <filesystem>
#include <iostream>

#include "path_finder.h"

std::istream &operator>>(std::istream &input, Location &point) {
  char c;
  if (input >> point.x >> c >> point.y) {
    return input;
  }
  input.setstate(std::ios::failbit);
  return input;
}

Grid GetGrid() {
  std::cout << "The current maze is:\n";
  Grid grid("5x6.board");
  grid.print();
  std::cout << "Continue with this maze? {Y|n} >> ";
  std::string input;
  getline(std::cin, input);
  if (input.find('n') != std::string::npos) {
    do {
      std::cout << "\nPlease provide path to your .board file, or EXIT >> ";
      getline(std::cin, input);
      if (input == "EXIT") {
        std::cout << "Good bye... 🙃";
        std::exit(0);
      }
    } while (!std::filesystem::exists(input));
    grid = Grid(input);
    std::cout << "\nMaze is:\n";
    grid.print();
  }
  return grid;
}

Location GetPoint(const std::string &name) {
  Location point{};
  std::cout << "Please provide your " << name << " \"x,y\" without quotes >> ";
  std::cin >> point;
  return point;
}

int main() {
  std::cout << "👋 Welcome to the Maze!\n";

  Grid grid = GetGrid();
  Location start = GetPoint("start");
  Location goal = GetPoint("goal");

  PathFinder path_finder(grid);
  std::cout << "🔎 Searching...\n";
  auto solution = path_finder.search(start, goal);
  solution.print();

  std::cout << "Until next time! 👍\n";
}
