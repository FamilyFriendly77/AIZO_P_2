
#ifndef EDGE_HPP
#define EDGE_HPP
class Edge {

  int origin;
  int destination;
  int weight;

public:
  Edge(int d, int w) : destination(d), weight(w) {}
  Edge(int o, int d, int w) : origin(o), destination(d), weight(w) {}
};

#endif
