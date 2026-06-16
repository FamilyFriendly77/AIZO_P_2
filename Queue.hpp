#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "Edge.hpp"
#include <cstddef>

class PriorityQueue {
  Edge *data;
  std::size_t size;
  std::size_t capacity;

  void heapifyUp(int index);
  void heapifyDown(int index);
  void resize();

public:
  PriorityQueue();
  ~PriorityQueue();
  void push(Edge payload);
  void pop();
  Edge top();
  bool isEmpty() const;
  std::size_t getSize() const;
};

#endif
