#include "DisjointSet.hpp"

DisjointSet::DisjointSet(int n) : n(n) {
  parent = new int[n];
  rank = new int[n];
  for (int i = 0; i < n; i++) {
    parent[i] = i;
    rank[i] = 0;
  }
}

DisjointSet::~DisjointSet() {
  delete[] parent;
  delete[] rank;
}

int DisjointSet::find(int i) {
  if (parent[i] == i)
    return i;
  return parent[i] = find(parent[i]);
}

void DisjointSet::unite(int i, int j) {
  int root_i = find(i);
  int root_j = find(j);

  if (root_i != root_j) {
    if (rank[root_i] < rank[root_j]) {
      parent[root_i] = root_j;
    } else if (rank[root_i] > rank[root_j]) {
      parent[root_j] = root_i;
    } else {
      parent[root_i] = root_j;
      rank[root_j]++;
    }
  }
}
