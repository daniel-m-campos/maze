#include "test.h"

#include "catch2/catch.hpp"

#include <iostream>
#include <vector>
using std::vector;
#include "../src/path_finder.h"

void PrintVector(vector<int> v) {
  std::cout << "{ ";
  for (auto item : v) {
    std::cout << item << " ";
  }
  std::cout << "}"
            << "\n";
}

void PrintVectorOfVectors(vector<vector<int>> v) {
  for (auto row : v) {
    std::cout << "{ ";
    for (auto col : row) {
      std::cout << col << " ";
    }
    std::cout << "}"
              << "\n";
  }
}

void PrintVectorOfVectors(vector<vector<State>> v) {
  for (auto row : v) {
    std::cout << "{ ";
    for (auto col : row) {
      std::cout << Grid::CellString(col) << " ";
    }
    std::cout << "}"
              << "\n";
  }
}

void TestHeuristic() {
  std::cout << "----------------------------------------------------------"
            << "\n";
  std::cout << "heuristic Function Test: ";
  if (PathFinder::Heuristic(Point{1, 2}, Point{3, 4}) != 4) {
    std::cout << "failed"
              << "\n";
    std::cout << "\n"
              << "heuristic(1, 2, 3, 4) = "
              << PathFinder::Heuristic(Point{1, 2}, Point{3, 4}) << "\n";
    std::cout << "Correct result: 4"
              << "\n";
    std::cout << "\n";
  } else if (PathFinder::Heuristic(Point{2, -1}, Point{4, -7}) != 8) {
    std::cout << "TestHeuristic Failed"
              << "\n";
    std::cout << "\n"
              << "heuristic(2, -1, 4, -7) = "
              << PathFinder::Heuristic(Point{2, -1}, Point{4, -7}) << "\n";
    std::cout << "Correct result: 8"
              << "\n";
    std::cout << "\n";
  } else {
    std::cout << "passed"
              << "\n";
  }
}

void TestAddToOpen() {
  std::cout << "----------------------------------------------------------"
            << "\n";
  std::cout << "AddToOpen Function Test: ";
  int x = 3;
  int y = 0;
  int g = 5;
  int h = 7;
  vector<vector<int>> open{{0, 0, 2, 9}, {1, 0, 2, 2}, {2, 0, 2, 4}};
  vector<vector<int>> solution_open = open;
  solution_open.push_back(vector<int>{3, 0, 5, 7});
  vector<vector<State>> grid{{State::kClosed, State::kObstacle, State::kEmpty,
                              State::kEmpty, State::kEmpty, State::kEmpty},
                             {State::kClosed, State::kObstacle, State::kEmpty,
                              State::kEmpty, State::kEmpty, State::kEmpty},
                             {State::kClosed, State::kObstacle, State::kEmpty,
                              State::kEmpty, State::kEmpty, State::kEmpty},
                             {State::kEmpty, State::kObstacle, State::kEmpty,
                              State::kEmpty, State::kEmpty, State::kEmpty},
                             {State::kEmpty, State::kEmpty, State::kEmpty,
                              State::kEmpty, State::kObstacle, State::kEmpty}};
  vector<vector<State>> solution_grid = grid;
  solution_grid[3][0] = State::kClosed;
  AddToOpen(x, y, g, h, open, grid);
  if (open != solution_open) {
    std::cout << "failed"
              << "\n";
    std::cout << "\n";
    std::cout << "Your open list is: "
              << "\n";
    PrintVectorOfVectors(open);
    std::cout << "Solution open list is: "
              << "\n";
    PrintVectorOfVectors(solution_open);
    std::cout << "\n";
  } else if (grid != solution_grid) {
    std::cout << "failed"
              << "\n";
    std::cout << "\n";
    std::cout << "Your grid is: "
              << "\n";
    PrintVectorOfVectors(grid);
    std::cout << "\n";
    std::cout << "Solution grid is: "
              << "\n";
    PrintVectorOfVectors(solution_grid);
    std::cout << "\n";
  } else {
    std::cout << "passed"
              << "\n";
  }
  return;
}

void TestCompare() {
  std::cout << "----------------------------------------------------------"
            << "\n";
  std::cout << "Compare Function Test: ";
  Node test_1{1, 2, 5, 6};
  Node test_2{1, 3, 5, 7};
  Node test_3{1, 2, 5, 8};
  Node test_4{1, 3, 5, 7};
  if (PathFinder::Compare(test_1, test_2)) {
    std::cout << "failed"
              << "\n";
    std::cout << "\n"
              << "a = ";
    PrintVector(test_1);
    std::cout << "b = ";
    PrintVector(test_2);
    std::cout << "Compare(a, b): " << Compare(test_1, test_2) << "\n";
    std::cout << "Correct answer: 0"
              << "\n";
    std::cout << "\n";
  } else if (!Compare(test_3, test_4)) {
    std::cout << "failed"
              << "\n";
    std::cout << "\n"
              << "a = ";
    PrintVector(test_3);
    std::cout << "b = ";
    PrintVector(test_4);
    std::cout << "Compare(a, b): " << Compare(test_3, test_4) << "\n";
    std::cout << "Correct answer: 1"
              << "\n";
    std::cout << "\n";
  } else {
    std::cout << "passed"
              << "\n";
  }
  return;
}

void TestSearch() {
  std::cout << "----------------------------------------------------------"
            << "\n";
  std::cout << "Search Function Test: ";
  int init[2]{0, 0};
  int goal[2]{4, 5};
  auto board = ReadBoardFile("1.board");

  std::std::cout.setstate(std::ios_base::failbit);  // Disable std::cout
  auto output = Search(board, init, goal);
  std::std::cout.clear();  // Enable std::cout

  vector<vector<State>> solution{
      {State::kStart, State::kObstacle, State::kEmpty, State::kEmpty,
       State::kEmpty, State::kEmpty},
      {State::kPath, State::kObstacle, State::kEmpty, State::kEmpty,
       State::kEmpty, State::kEmpty},
      {State::kPath, State::kObstacle, State::kEmpty, State::kClosed,
       State::kClosed, State::kClosed},
      {State::kPath, State::kObstacle, State::kClosed, State::kPath,
       State::kPath, State::kPath},
      {State::kPath, State::kPath, State::kPath, State::kPath, State::kObstacle,
       State::kFinish}};

  if (output != solution) {
    std::cout << "failed"
              << "\n";
    std::cout << "Search(board, {0,0}, {4,5})"
              << "\n";
    std::cout << "Solution board: "
              << "\n";
    PrintVectorOfVectors(solution);
    std::cout << "Your board: "
              << "\n";
    PrintVectorOfVectors(output);
    std::cout << "\n";
  } else {
    std::cout << "passed"
              << "\n";
  }
  return;
}

void TestCheckValidCell() {
  std::cout << "----------------------------------------------------------"
            << "\n";
  std::cout << "CheckValidCell Function Test: ";
  vector<vector<State>> grid{{State::kClosed, State::kObstacle, State::kEmpty,
                              State::kEmpty, State::kEmpty, State::kEmpty},
                             {State::kClosed, State::kObstacle, State::kEmpty,
                              State::kEmpty, State::kEmpty, State::kEmpty},
                             {State::kClosed, State::kObstacle, State::kEmpty,
                              State::kEmpty, State::kEmpty, State::kEmpty},
                             {State::kClosed, State::kObstacle, State::kEmpty,
                              State::kEmpty, State::kEmpty, State::kEmpty},
                             {State::kClosed, State::kClosed, State::kEmpty,
                              State::kEmpty, State::kObstacle, State::kEmpty}};

  if (CheckValidCell(0, 0, grid)) {
    std::cout << "failed"
              << "\n";
    std::cout << "\n"
              << "Test grid is: "
              << "\n";
    PrintVectorOfVectors(grid);
    std::cout << "Cell checked: (0, 0)"
              << "\n";
    std::cout << "\n";
  } else if (!CheckValidCell(4, 2, grid)) {
    std::cout << "failed"
              << "\n";
    std::cout << "\n"
              << "Test grid is: "
              << "\n";
    PrintVectorOfVectors(grid);
    std::cout << "Cell checked: (4, 2)"
              << "\n";
    std::cout << "\n";
  } else {
    std::cout << "passed"
              << "\n";
  }
}

void TestExpandNeighbors() {
  std::cout << "----------------------------------------------------------"
            << "\n";
  std::cout << "ExpandNeighbors Function Test: ";
  vector<int> current{4, 2, 7, 3};
  int goal[2]{4, 5};
  vector<vector<int>> open{{4, 2, 7, 3}};
  vector<vector<int>> solution_open = open;
  solution_open.push_back(vector<int>{3, 2, 8, 4});
  solution_open.push_back(vector<int>{4, 3, 8, 2});
  vector<vector<State>> grid{{State::kClosed, State::kObstacle, State::kEmpty,
                              State::kEmpty, State::kEmpty, State::kEmpty},
                             {State::kClosed, State::kObstacle, State::kEmpty,
                              State::kEmpty, State::kEmpty, State::kEmpty},
                             {State::kClosed, State::kObstacle, State::kEmpty,
                              State::kEmpty, State::kEmpty, State::kEmpty},
                             {State::kClosed, State::kObstacle, State::kEmpty,
                              State::kEmpty, State::kEmpty, State::kEmpty},
                             {State::kClosed, State::kClosed, State::kEmpty,
                              State::kEmpty, State::kObstacle, State::kEmpty}};
  vector<vector<State>> solution_grid = grid;
  solution_grid[3][2] = State::kClosed;
  solution_grid[4][3] = State::kClosed;
  ExpandNeighbors(current, goal, open, grid);
  CellSort(&open);
  CellSort(&solution_open);
  if (open != solution_open) {
    std::cout << "failed"
              << "\n";
    std::cout << "\n";
    std::cout << "Your open list is: "
              << "\n";
    PrintVectorOfVectors(open);
    std::cout << "Solution open list is: "
              << "\n";
    PrintVectorOfVectors(solution_open);
    std::cout << "\n";
  } else if (grid != solution_grid) {
    std::cout << "failed"
              << "\n";
    std::cout << "\n";
    std::cout << "Your grid is: "
              << "\n";
    PrintVectorOfVectors(grid);
    std::cout << "\n";
    std::cout << "Solution grid is: "
              << "\n";
    PrintVectorOfVectors(solution_grid);
    std::cout << "\n";
  } else {
    std::cout << "passed"
              << "\n";
  }
  std::cout << "----------------------------------------------------------"
            << "\n";
  return;
}