#include "Edge.hpp"
#include "Graph.hpp"
#include <string>
class DataUtility {
private:
  static Edge **neighbourListFromMatrix(int *matrix, int V, int *&outSizes);

public:
  Graph generateGraph(int V, float density, bool isDirected);
  Graph readGraph(std::string filename, bool isDirected);
};
