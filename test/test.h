#ifndef MAZE__TEST_H_
#define MAZE__TEST_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../src/grid.h"

void PrintVector(std::vector<int>);
void PrintVectorOfVectors(std::vector<std::vector<int>>);
void PrintVectorOfVectors(std::vector<std::vector<State>>);
void TestHeuristic();
void TestAddToOpen();
void TestCompare();
void TestSearch();
void TestCheckValidCell();
void TestExpandNeighbors();

#endif  // MAZE__TEST_H_
