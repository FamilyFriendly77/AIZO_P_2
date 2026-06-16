
#ifndef EDGE_HPP
#define EDGE_HPP
class Edge {
public:
  int origin;
  int destination;
  int weight;

  Edge() : destination(0), weight(0) {}
  Edge(int d, int w) : destination(d), weight(w) {}
  Edge(int o, int d, int w) : origin(o), destination(d), weight(w) {}
};

#endif
