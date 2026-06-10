#include "Edge.hpp"
#include <cstddef>
class PriorityQueue {
  Edge *data;
  void sort();
  std::size_t size;

public:
  void push(Edge payload);
  void pop();
};
