#include <filesystem>
#include <iostream>

#include "path_finder.h"

std::istream& operator>>(std::istream& input, Point& point) {
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
  grid.Print();
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
    grid.Print();
  }
  return grid;
}

Point GetPoint(const std::string& name) {
  Point point{};
  std::cout << "Please provide your " << name << " \"x,y\" without quotes >> ";
  std::cin >> point;
  return point;
}

int main() {
  std::cout << "👋 Welcome to the Maze!\n";
  Grid grid = GetGrid();
  Point start = GetPoint("start");
  Point goal = GetPoint("goal");

  PathFinder path_finder(grid);
  std::cout << "🔎 Searching...  \n";
  auto solution = path_finder.Search(start, goal);
  std::cout << "🤖 Found a path!\n";
  solution.Print();

  std::cout << "Until next time! 👍";
}