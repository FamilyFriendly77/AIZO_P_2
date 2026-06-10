#include "config.hpp"
int main(int argsC, char **argsV) {
  srand(Config::randomSeed.getValue() ? Config::randomSeed.getValue()
                                      : time(NULL));
}
