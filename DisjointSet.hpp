#ifndef DISJOINT_SET_HPP
#define DISJOINT_SET_HPP

class DisjointSet {
  int *parent;
  int *rank;
  int n;

public:
  DisjointSet(int n);
  ~DisjointSet() {
    delete[] parent;
    delete[] rank;
  };
  int find(int i);
  void unite(int i, int j);
};

#endif
