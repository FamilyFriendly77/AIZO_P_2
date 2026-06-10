#include "config.hpp"
#include <chrono>
#include <cstdlib>
#include <iostream>
class TestingUtility {
  bool testShortestPath(int *Path, int *Graph);
  bool testShortestPath(int *Path, int **Graph);
  bool testMST(int *MST, int *Graph);
  bool testMST(int *MST, int **Graph);
};
