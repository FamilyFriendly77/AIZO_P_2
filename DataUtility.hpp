#include "Edge.hpp"
class DataUtility {
public:
  void generateGraph(int V, float density, int *matrixDestination,
                     Edge **listDestination);
  void readGraph(int *matrixDestionation, Edge **listDestionation);
};
