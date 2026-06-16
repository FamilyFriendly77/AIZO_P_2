#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Edge.hpp"

class Graph {
public:
  Edge **neighbourList;
  int *neighbourListSizes;
  int *adjacencyMatrix;
  int vertices;

  Graph(int *adjacencyMatrix, Edge **neighbourList, int *neighbourListSizes,
        int vertices)
      : adjacencyMatrix(adjacencyMatrix), neighbourList(neighbourList),
        neighbourListSizes(neighbourListSizes), vertices(vertices) {}

  void printGraph();

  ~Graph() {
    if (adjacencyMatrix != nullptr) {
      delete[] adjacencyMatrix;
    }
    if (neighbourListSizes != nullptr) {
      delete[] neighbourListSizes;
    }
    if (neighbourList != nullptr) {
      for (int i = 0; i < vertices; i++) {
        if (neighbourList[i] != nullptr) {
          delete[] neighbourList[i];
        }
      }
      delete[] neighbourList;
    }
  }
};

#endif
