#include "Queue.hpp"
#include <stdexcept>

PriorityQueue::PriorityQueue() : data(nullptr), size(0), capacity(0) {
  resize();
}

PriorityQueue::~PriorityQueue() { delete[] data; }

void PriorityQueue::resize() {
  std::size_t newCapacity = (capacity == 0) ? 10 : capacity * 2;
  Edge *newData = new Edge[newCapacity];
  for (std::size_t i = 0; i < size; ++i) {
    newData[i] = data[i];
  }
  delete[] data;
  data = newData;
  capacity = newCapacity;
}

void PriorityQueue::heapifyUp(int index) {
  while (index > 0) {
    int parent = (index - 1) / 2;
    if (data[index].weight < data[parent].weight) {
      Edge temp = data[index];
      data[index] = data[parent];
      data[parent] = temp;
      index = parent;
    } else {
      break;
    }
  }
}

void PriorityQueue::heapifyDown(int index) {
  while (true) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < (int)size && data[left].weight < data[smallest].weight) {
      smallest = left;
    }
    if (right < (int)size && data[right].weight < data[smallest].weight) {
      smallest = right;
    }

    if (smallest != index) {
      Edge temp = data[index];
      data[index] = data[smallest];
      data[smallest] = temp;
      index = smallest;
    } else {
      break;
    }
  }
}

void PriorityQueue::push(Edge payload) {
  if (size == capacity) {
    resize();
  }
  data[size] = payload;
  heapifyUp(size);
  size++;
}

void PriorityQueue::pop() {
  if (isEmpty())
    return;
  data[0] = data[size - 1];
  size--;
  heapifyDown(0);
}

Edge PriorityQueue::top() {
  if (isEmpty())
    throw std::runtime_error("Queue is empty");
  return data[0];
}

bool PriorityQueue::isEmpty() const { return size == 0; }

std::size_t PriorityQueue::getSize() const { return size; }
