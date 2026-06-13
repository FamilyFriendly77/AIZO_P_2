#include "DataUtility.hpp"
#include "Edge.hpp"
#include "Graph.hpp"
#include <cstdlib>
void DataUtility::generateGraph(int V, float density, int *matrixDestination,
                                int **listDestination) {

  int *tempMatrix = (int *)std::malloc(V * V * sizeof(int));
  Edge **tempList = (Edge **)std::malloc(V * (sizeof(Edge *)));
  int currentEdges = V - 1;
  int randomIndex;
  int fullGraphEdgeCount = (V * V - V) / 2;
  for (int i = 0; i < V * V; i++) {
    tempMatrix[i] = 0;
  }
  for (int i = 0; i * V + i + 1 < V * V; i++) {
    tempMatrix[i * V + i + 1] = rand() % 101;
  }
  while (currentEdges < fullGraphEdgeCount * density) {
    randomIndex = rand() % V * V;
    if (!tempMatrix[randomIndex]) {
      tempMatrix[randomIndex] = rand() % 101;
      currentEdges++;
    }
  }
  for (int i = 0; i < V; i++) {
    int EdgeCounter = 0;
    for (int j = 0; j < V; j++) {
      if (tempMatrix[i * V + j]) {
        EdgeCounter++;
      }
    }
    int edgeIndex = 0;
    Edge *tempNeighbourList = (Edge *)std::malloc(EdgeCounter * sizeof(Edge *));
    for (int j = 0; j < V; j++) {
      if (tempMatrix[i * V + j])
        tempNeighbourList[edgeIndex] = Edge(j, tempMatrix[i * V + j]);
    }
    tempList[i] = tempNeighbourList;
  }
}
