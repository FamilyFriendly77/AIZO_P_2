#include "config.hpp"
#include "dataUtility.hpp"
#include <chrono>
#include <cstdlib>
#include <iostream>
template <typename T> class TestingUtility {
private:
public:
  // returns average sorting time for specific array and specific alg
  double testSortingTime(void (*sort)(T *, int), T *array, int arrayLen) {
    std::chrono::duration<double> result(0);
    T *arr = (T *)malloc(arrayLen * sizeof(T));
    std::memcpy(arr, array, arrayLen * sizeof(T));
    // benchmark
    if (arr == nullptr)
      return 0.0;
    auto start = std::chrono::high_resolution_clock::now();
    sort(arr, arrayLen);
    auto end = std::chrono::high_resolution_clock::now();
    if (Config::printAfterSorting.getValue() || Config::inTestMode.getValue()) {
      std::cout << "SORTED ARRAY:" << std::endl;
      for (int i = 0; i < arrayLen; i++) {

        std::cout << arr[i] << std::endl;
      }
    }
    if (Config::testIfSorted.getValue() || Config::inTestMode.getValue()) {
      if (isSorted(arr, arrayLen)) {
        std::cout << "Sorting was successful!" << std::endl;
      } else {
        std::cout << "Somethig went wrong while sorting!" << std::endl;
      }
      std::cout << "===============================" << std::endl;
    }

    result = (end - start);

    free(arr);
    return result.count();
  };
  bool isSorted(T *arr, int arrLen) {
    for (int i = 0; i < arrLen - 1; i++) {
      if (arr[i] > arr[i + 1])
        return false;
    }
    return true;
  }
};
