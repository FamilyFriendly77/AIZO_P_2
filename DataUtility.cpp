#include "DataUtility.hpp"
#include <cstdlib>

void DataUtility::generateGraph(int V, float density, int *matrixDestination,
                                int **listDestination) {

  int *tempMatrix = (int *)std::malloc(V * V * sizeof(int));
  int **tempList = (int **)std::malloc(V * (sizeof(int *)));
  int currentEdges = V - 1;
  int randomIndex;
  int fullGraphEdgeCount = V * V;
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
}
