#include "DataUtility.hpp"
#include "config.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

Graph DataUtility::generateGraph(int V, float density, bool isDirected) {
  int *tempMatrix = new int[V * V];
  for (int i = 0; i < V * V; i++)
    tempMatrix[i] = 0;

  int currentEdges = 0;
  for (int i = 0; i < V - 1; i++) {
    int weight = (rand() % 100) + 1;
    tempMatrix[i * V + (i + 1)] = weight;
    if (!isDirected)
      tempMatrix[(i + 1) * V + i] = weight;
    currentEdges++;
  }

  int maxEdges = isDirected ? (V * V - V) : (V * V - V) / 2;
  int targetEdges = (int)(maxEdges * density);

  while (currentEdges < targetEdges) {
    int u = rand() % V;
    int v = rand() % V;
    if (u != v && tempMatrix[u * V + v] == 0) {
      int weight = (rand() % 100) + 1;
      tempMatrix[u * V + v] = weight;
      if (!isDirected)
        tempMatrix[v * V + u] = weight;
      currentEdges++;
    }
  }

  int *sizes = nullptr;
  Edge **tempList = neighbourListFromMatrix(tempMatrix, V, sizes);
  Graph g(tempMatrix, tempList, sizes, V);

  if (Config::printAfterGenerating.getValue()) {
    g.printGraph();
  }

  return g;
}

Graph DataUtility::readGraph(std::string filename, bool isDirected) {
  std::ifstream file(filename);
  int V, E, origin, destination, weight;

  if (!file)
    throw std::runtime_error("Cannot open graph file");

  file >> E >> V;
  int *tempMatrix = new int[V * V];
  for (int i = 0; i < V * V; i++)
    tempMatrix[i] = 0;

  for (int i = 0; i < E; i++) {
    file >> origin >> destination >> weight;
    if (origin < V && destination < V) {
      tempMatrix[origin * V + destination] = weight;
      if (!isDirected)
        tempMatrix[destination * V + origin] = weight;
    }
  }

  int *sizes = nullptr;
  Edge **tempList = neighbourListFromMatrix(tempMatrix, V, sizes);
  Graph g(tempMatrix, tempList, sizes, V);

  if (Config::printAfterGenerating.getValue()) {
    g.printGraph();
  }

  return g;
}

Edge **DataUtility::neighbourListFromMatrix(int *matrix, int V,
                                            int *&outSizes) {
  Edge **tempList = new Edge *[V];
  outSizes = new int[V];
  for (int i = 0; i < V; i++) {
    int edgeCounter = 0;
    for (int j = 0; j < V; j++) {
      if (matrix[i * V + j])
        edgeCounter++;
    }
    outSizes[i] = edgeCounter;
    Edge *tempNeighbourList = new Edge[edgeCounter];
    int edgeIndex = 0;
    for (int j = 0; j < V; j++) {
      if (matrix[i * V + j]) {
        tempNeighbourList[edgeIndex] = Edge(i, j, matrix[i * V + j]);
        edgeIndex++;
      }
    }
    tempList[i] = tempNeighbourList;
  }
  return tempList;
}
