#define CATCH_CONFIG_MAIN
#include <iostream>
#include <vector>

#include "catch2/catch.hpp"
using std::vector;
#include "path_finder.h"

void PrintVector(const vector<int>& v) {
  std::cout << "{ ";
  for (auto item : v) {
    std::cout << item << " ";
  }
  std::cout << "}"
            << "\n";
}

void PrintVectorOfVectors(const vector<vector<int>>& v) {
  for (const auto& row : v) {
    std::cout << "{ ";
    for (auto col : row) {
      std::cout << col << " ";
    }
    std::cout << "}"
              << "\n";
  }
}

void PrintVectorOfVectors(const vector<vector<State>>& v) {
  for (const auto& row : v) {
    std::cout << "{ ";
    for (auto col : row) {
      std::cout << Grid::CellString(col) << " ";
    }
    std::cout << "}"
              << "\n";
  }
}

TEST_CASE("Heuristic Function Test", "[HeuristicTests]") {
  PathFinder path_finder;
  CHECK(path_finder.Heuristic(Point{1, 2}, Point{3, 4}) == 4);
  CHECK(path_finder.Heuristic(Point{2, -1}, Point{4, -7}) == 8);
}

TEST_CASE("AddToOpen Function Test", "[AddToOpenTests]") {
  vector<Node> open;
  vector<Node> solution_open = open;
  solution_open.push_back({{3, 0}, 5, 7});

  Grid grid({{State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty,
              State::kEmpty, State::kEmpty},
             {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty,
              State::kEmpty, State::kEmpty},
             {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty,
              State::kEmpty, State::kEmpty},
             {State::kEmpty, State::kObstacle, State::kEmpty, State::kEmpty,
              State::kEmpty, State::kEmpty},
             {State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty,
              State::kObstacle, State::kEmpty}});
  Grid solution_grid = grid;
  solution_grid.Close({3, 0});

  PathFinder path_finder(grid);
  path_finder.AddToOpen({{3, 0}, 5, 7});
  SECTION("Open is updated") {
    CHECK(path_finder.GetOpenNodes() == solution_open);
  }
  SECTION("Grid is updated") { CHECK(path_finder.GetGrid() == solution_grid); }
}

TEST_CASE("Compare Function Test", "[CompareTests]") {
  SECTION("test_1 <= test_2") {
    Node test_1{1, 2, 5, 6};
    Node test_2{1, 3, 5, 7};
    CHECK(PathFinder::Compare(test_1, test_2) == false);
  }
  SECTION("test_3 > test_4") {
    Node test_3{1, 2, 5, 8};
    Node test_4{1, 3, 5, 7};
    CHECK(PathFinder::Compare(test_3, test_4) == true);
  }
}

TEST_CASE("Search Function Test", "[SearchTests]") {
  auto board = Grid("5x6.board");
  auto path_finder = PathFinder(board);
  auto actual = path_finder.Search({0, 0}, {4, 5});
  Grid expected({{State::kStart, State::kObstacle, State::kEmpty, State::kEmpty,
                  State::kEmpty, State::kEmpty},
                 {State::kPath, State::kObstacle, State::kEmpty, State::kEmpty,
                  State::kEmpty, State::kEmpty},
                 {State::kPath, State::kObstacle, State::kEmpty, State::kClosed,
                  State::kClosed, State::kClosed},
                 {State::kPath, State::kObstacle, State::kClosed, State::kPath,
                  State::kPath, State::kPath},
                 {State::kPath, State::kPath, State::kPath, State::kPath,
                  State::kObstacle, State::kFinish}});
  std::cout << "===== Actual =====" << std::endl;
  actual.Print();
  std::cout << "===== Expected =====" << std::endl;
  expected.Print();
  CHECK(actual == expected);
}

TEST_CASE("IsValid Function Test", "[CheckValidCellTests]") {
  Grid grid({{State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty,
              State::kEmpty, State::kEmpty},
             {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty,
              State::kEmpty, State::kEmpty},
             {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty,
              State::kEmpty, State::kEmpty},
             {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty,
              State::kEmpty, State::kEmpty},
             {State::kClosed, State::kClosed, State::kEmpty, State::kEmpty,
              State::kObstacle, State::kEmpty}});
  CHECK(grid.IsValid({0, 0}) == false);
  CHECK(grid.IsValid({4, 2}) == true);
}

TEST_CASE("ExpandNeighbors Function Test", "[ExpandNeighborsTests]") {
  Node current{4, 2, 7, 3};
  auto grid = Grid({{State::kClosed, State::kObstacle, State::kEmpty,
                     State::kEmpty, State::kEmpty, State::kEmpty},
                    {State::kClosed, State::kObstacle, State::kEmpty,
                     State::kEmpty, State::kEmpty, State::kEmpty},
                    {State::kClosed, State::kObstacle, State::kEmpty,
                     State::kEmpty, State::kEmpty, State::kEmpty},
                    {State::kClosed, State::kObstacle, State::kEmpty,
                     State::kEmpty, State::kEmpty, State::kEmpty},
                    {State::kClosed, State::kClosed, State::kEmpty,
                     State::kEmpty, State::kObstacle, State::kEmpty}});
  auto expected_grid = grid;
  expected_grid.Close(current.point);
  expected_grid.Close({3, 2});
  expected_grid.Close({4, 3});

  vector<Node> open{current};
  auto expected_open = open;
  expected_open.push_back({3, 2, 8, 4});
  expected_open.push_back({4, 3, 8, 2});

  PathFinder path_finder(grid);
  path_finder.AddToOpen(current);
  path_finder.ExpandNeighbors(current, {4, 5});

  SECTION("Open nodes are correct") {
    CHECK(path_finder.GetOpenNodes() == expected_open);
  }
  SECTION("Grid is correct") { CHECK(path_finder.GetGrid() == expected_grid); }
}