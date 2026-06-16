#ifndef SOLVING_UTILITY_HPP
#define SOLVING_UTILITY_HPP

#include "Graph.hpp"

class SolvingUtility {
public:
  static double primMatrix(Graph &g, int startNode);
  static double primList(Graph &g, int startNode);
  static double kruskalMatrix(Graph &g);
  static double kruskalList(Graph &g);
  static double dijkstraMatrix(Graph &g, int startNode, int endNode);
  static double dijkstraList(Graph &g, int startNode, int endNode);
  static double fordBellmanMatrix(Graph &g, int startNode, int endNode);
  static double fordBellmanList(Graph &g, int startNode, int endNode);

private:
  static void printPath(int *parent, int endNode, int startNode);
};

#endif
