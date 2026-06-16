#include "SolvingUtility.hpp"
#include "DisjointSet.hpp"
#include "Queue.hpp"
#include "config.hpp"
#include <chrono>
#include <climits>
#include <iostream>

void SolvingUtility::printPath(int *parent, int endNode, int startNode) {
  if (endNode == startNode) {
    std::cout << startNode;
    return;
  }
  if (parent[endNode] == -1) {
    std::cout << "No path";
    return;
  }
  printPath(parent, parent[endNode], startNode);
  std::cout << " -> " << endNode;
}

double SolvingUtility::primMatrix(Graph &g, int startNode) {
  auto start = std::chrono::high_resolution_clock::now();
  int V = g.vertices;
  int *matrix = g.adjacencyMatrix;
  bool *visited = new bool[V];
  int totalWeight = 0;
  PriorityQueue pq;
  Edge *mstEdges = nullptr;
  int mstIdx = 0;
  if (Config::printAfterSolving.getValue() || Config::inTestMode.getValue()) {
    mstEdges = new Edge[V - 1];
  }
  for (int i = 0; i < V; i++)
    visited[i] = false;
  visited[startNode] = true;
  for (int i = 0; i < V; i++) {
    if (matrix[startNode * V + i] > 0) {
      pq.push(Edge(startNode, i, matrix[startNode * V + i]));
    }
  }
  int edgesFound = 0;
  while (!pq.isEmpty() && edgesFound < V - 1) {
    Edge e = pq.top();
    pq.pop();
    if (visited[e.destination])
      continue;
    visited[e.destination] = true;
    totalWeight += e.weight;
    if (mstEdges)
      mstEdges[mstIdx++] = e;
    edgesFound++;
    for (int i = 0; i < V; i++) {
      if (!visited[i] && matrix[e.destination * V + i] > 0) {
        pq.push(Edge(e.destination, i, matrix[e.destination * V + i]));
      }
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  if (Config::printAfterSolving.getValue() || Config::inTestMode.getValue()) {
    std::cout << "MST Prim (Matrix):" << std::endl;
    for (int i = 0; i < mstIdx; i++) {
      std::cout << "(" << mstEdges[i].origin << "," << mstEdges[i].destination
                << ") [" << mstEdges[i].weight << "]" << std::endl;
    }
    std::cout << "Total MST weight: " << totalWeight << std::endl;
    delete[] mstEdges;
  }
  delete[] visited;
  return std::chrono::duration<double, std::milli>(end - start).count();
}

double SolvingUtility::primList(Graph &g, int startNode) {
  auto start = std::chrono::high_resolution_clock::now();
  int V = g.vertices;
  Edge **list = g.neighbourList;
  int *sizes = g.neighbourListSizes;
  bool *visited = new bool[V];
  int totalWeight = 0;
  PriorityQueue pq;
  Edge *mstEdges = nullptr;
  int mstIdx = 0;
  if (Config::printAfterSolving.getValue() || Config::inTestMode.getValue()) {
    mstEdges = new Edge[V - 1];
  }
  for (int i = 0; i < V; i++)
    visited[i] = false;
  visited[startNode] = true;
  for (int i = 0; i < sizes[startNode]; i++) {
    pq.push(list[startNode][i]);
  }
  int edgesFound = 0;
  while (!pq.isEmpty() && edgesFound < V - 1) {
    Edge e = pq.top();
    pq.pop();
    if (visited[e.destination])
      continue;
    visited[e.destination] = true;
    totalWeight += e.weight;
    if (mstEdges)
      mstEdges[mstIdx++] = e;
    edgesFound++;
    for (int i = 0; i < sizes[e.destination]; i++) {
      if (!visited[list[e.destination][i].destination]) {
        pq.push(list[e.destination][i]);
      }
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  if (Config::printAfterSolving.getValue() || Config::inTestMode.getValue()) {
    std::cout << "MST Prim (List):" << std::endl;
    for (int i = 0; i < mstIdx; i++) {
      std::cout << "(" << mstEdges[i].origin << "," << mstEdges[i].destination
                << ") [" << mstEdges[i].weight << "]" << std::endl;
    }
    std::cout << "Total MST weight: " << totalWeight << std::endl;
    delete[] mstEdges;
  }
  delete[] visited;
  return std::chrono::duration<double, std::milli>(end - start).count();
}

double SolvingUtility::kruskalMatrix(Graph &g) {
  auto start = std::chrono::high_resolution_clock::now();
  int V = g.vertices;
  int *matrix = g.adjacencyMatrix;
  PriorityQueue pq;
  for (int i = 0; i < V; i++) {
    for (int j = i + 1; j < V; j++) {
      if (matrix[i * V + j] > 0) {
        pq.push(Edge(i, j, matrix[i * V + j]));
      }
    }
  }
  DisjointSet ds(V);
  int totalWeight = 0;
  Edge *mstEdges = nullptr;
  int mstIdx = 0;
  if (Config::printAfterSolving.getValue() || Config::inTestMode.getValue()) {
    mstEdges = new Edge[V - 1];
  }
  int edgesFound = 0;
  while (!pq.isEmpty() && edgesFound < V - 1) {
    Edge e = pq.top();
    pq.pop();
    if (ds.find(e.origin) != ds.find(e.destination)) {
      ds.unite(e.origin, e.destination);
      totalWeight += e.weight;
      if (mstEdges)
        mstEdges[mstIdx++] = e;
      edgesFound++;
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  if (Config::printAfterSolving.getValue() || Config::inTestMode.getValue()) {
    std::cout << "MST Kruskal (Matrix):" << std::endl;
    for (int i = 0; i < mstIdx; i++) {
      std::cout << "(" << mstEdges[i].origin << "," << mstEdges[i].destination
                << ") [" << mstEdges[i].weight << "]" << std::endl;
    }
    std::cout << "Total MST weight: " << totalWeight << std::endl;
    delete[] mstEdges;
  }
  return std::chrono::duration<double, std::milli>(end - start).count();
}

double SolvingUtility::kruskalList(Graph &g) {
  auto start = std::chrono::high_resolution_clock::now();
  int V = g.vertices;
  Edge **list = g.neighbourList;
  int *sizes = g.neighbourListSizes;
  PriorityQueue pq;
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < sizes[i]; j++) {
      if (i < list[i][j].destination) {
        pq.push(list[i][j]);
      }
    }
  }
  DisjointSet ds(V);
  int totalWeight = 0;
  Edge *mstEdges = nullptr;
  int mstIdx = 0;
  if (Config::printAfterSolving.getValue() || Config::inTestMode.getValue()) {
    mstEdges = new Edge[V - 1];
  }
  int edgesFound = 0;
  while (!pq.isEmpty() && edgesFound < V - 1) {
    Edge e = pq.top();
    pq.pop();
    if (ds.find(e.origin) != ds.find(e.destination)) {
      ds.unite(e.origin, e.destination);
      totalWeight += e.weight;
      if (mstEdges)
        mstEdges[mstIdx++] = e;
      edgesFound++;
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  if (Config::printAfterSolving.getValue() || Config::inTestMode.getValue()) {
    std::cout << "MST Kruskal (List):" << std::endl;
    for (int i = 0; i < mstIdx; i++) {
      std::cout << "(" << mstEdges[i].origin << "," << mstEdges[i].destination
                << ") [" << mstEdges[i].weight << "]" << std::endl;
    }
    std::cout << "Total MST weight: " << totalWeight << std::endl;
    delete[] mstEdges;
  }
  return std::chrono::duration<double, std::milli>(end - start).count();
}

double SolvingUtility::dijkstraMatrix(Graph &g, int startNode, int endNode) {
  auto start = std::chrono::high_resolution_clock::now();
  int V = g.vertices;
  int *matrix = g.adjacencyMatrix;
  int *dist = new int[V];
  int *parent = new int[V];
  for (int i = 0; i < V; i++) {
    dist[i] = INT_MAX;
    parent[i] = -1;
  }
  PriorityQueue pq;
  dist[startNode] = 0;
  pq.push(Edge(-1, startNode, 0));
  while (!pq.isEmpty()) {
    Edge top = pq.top();
    pq.pop();
    int u = top.destination;
    if (top.weight > dist[u])
      continue;
    for (int v = 0; v < V; v++) {
      if (matrix[u * V + v] > 0) {
        if (dist[u] + matrix[u * V + v] < dist[v]) {
          dist[v] = dist[u] + matrix[u * V + v];
          parent[v] = u;
          pq.push(Edge(u, v, dist[v]));
        }
      }
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  if (Config::printAfterSolving.getValue() || Config::inTestMode.getValue()) {
    std::cout << "Dijkstra (Matrix): Cost = "
              << (dist[endNode] == INT_MAX ? -1 : dist[endNode]) << " Path: ";
    printPath(parent, endNode, startNode);
    std::cout << std::endl;
  }
  delete[] dist;
  delete[] parent;
  return std::chrono::duration<double, std::milli>(end - start).count();
}

double SolvingUtility::dijkstraList(Graph &g, int startNode, int endNode) {
  auto start = std::chrono::high_resolution_clock::now();
  int V = g.vertices;
  Edge **list = g.neighbourList;
  int *sizes = g.neighbourListSizes;
  int *dist = new int[V];
  int *parent = new int[V];
  for (int i = 0; i < V; i++) {
    dist[i] = INT_MAX;
    parent[i] = -1;
  }
  PriorityQueue pq;
  dist[startNode] = 0;
  pq.push(Edge(-1, startNode, 0));
  while (!pq.isEmpty()) {
    Edge top = pq.top();
    pq.pop();
    int u = top.destination;
    if (top.weight > dist[u])
      continue;
    for (int i = 0; i < sizes[u]; i++) {
      Edge e = list[u][i];
      if (dist[u] + e.weight < dist[e.destination]) {
        dist[e.destination] = dist[u] + e.weight;
        parent[e.destination] = u;
        pq.push(Edge(u, e.destination, dist[e.destination]));
      }
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  if (Config::printAfterSolving.getValue() || Config::inTestMode.getValue()) {
    std::cout << "Dijkstra (List): Cost = "
              << (dist[endNode] == INT_MAX ? -1 : dist[endNode]) << " Path: ";
    printPath(parent, endNode, startNode);
    std::cout << std::endl;
  }
  delete[] dist;
  delete[] parent;
  return std::chrono::duration<double, std::milli>(end - start).count();
}

double SolvingUtility::fordBellmanMatrix(Graph &g, int startNode, int endNode) {
  auto start = std::chrono::high_resolution_clock::now();
  int V = g.vertices;
  int *matrix = g.adjacencyMatrix;
  int *dist = new int[V];
  int *parent = new int[V];
  for (int i = 0; i < V; i++) {
    dist[i] = INT_MAX;
    parent[i] = -1;
  }
  dist[startNode] = 0;
  for (int i = 1; i < V; i++) {
    for (int u = 0; u < V; u++) {
      if (dist[u] == INT_MAX)
        continue;
      for (int v = 0; v < V; v++) {
        if (matrix[u * V + v] > 0 &&
            dist[u] + (long long)matrix[u * V + v] < dist[v]) {
          dist[v] = (int)(dist[u] + matrix[u * V + v]);
          parent[v] = u;
        }
      }
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  if (Config::printAfterSolving.getValue() || Config::inTestMode.getValue()) {
    std::cout << "Ford-Bellman (Matrix): Cost = "
              << (dist[endNode] == INT_MAX ? -1 : dist[endNode]) << " Path: ";
    printPath(parent, endNode, startNode);
    std::cout << std::endl;
  }
  delete[] dist;
  delete[] parent;
  return std::chrono::duration<double, std::milli>(end - start).count();
}

double SolvingUtility::fordBellmanList(Graph &g, int startNode, int endNode) {
  auto start = std::chrono::high_resolution_clock::now();
  int V = g.vertices;
  Edge **list = g.neighbourList;
  int *sizes = g.neighbourListSizes;
  int *dist = new int[V];
  int *parent = new int[V];
  for (int i = 0; i < V; i++) {
    dist[i] = INT_MAX;
    parent[i] = -1;
  }
  dist[startNode] = 0;
  for (int i = 1; i < V; i++) {
    for (int u = 0; u < V; u++) {
      if (dist[u] == INT_MAX)
        continue;
      for (int j = 0; j < sizes[u]; j++) {
        Edge e = list[u][j];
        if (dist[u] + (long long)e.weight < dist[e.destination]) {
          dist[e.destination] = (int)(dist[u] + e.weight);
          parent[e.destination] = u;
        }
      }
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  if (Config::printAfterSolving.getValue() || Config::inTestMode.getValue()) {
    std::cout << "Ford-Bellman (List): Cost = "
              << (dist[endNode] == INT_MAX ? -1 : dist[endNode]) << " Path: ";
    printPath(parent, endNode, startNode);
    std::cout << std::endl;
  }
  delete[] dist;
  delete[] parent;
  return std::chrono::duration<double, std::milli>(end - start).count();
}
