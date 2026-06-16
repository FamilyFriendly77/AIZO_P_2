#include "DataUtility.hpp"
#include "SolvingUtility.hpp"
#include "config.hpp"
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

void runAutomatedBenchmarking() {
  DataUtility du;
  std::vector<int> nodeCounts = Config::testCasesNodeCounts.getValue();
  std::vector<double> densities = Config::testCasesDensities.getValue();
  int repetitions = Config::testRepetitionCounter.getValue();
  std::string alg = Config::testAlg.getValue();

  std::cout << "--- Performance Testing Mode ---\n";
  std::cout << "Algorithm Selection: " << alg << "\n";
  std::cout << "Repetitions per case: " << repetitions << "\n\n";

  Config::printAfterSolving.setSetting(false);
  Config::printAfterGenerating.setSetting(false);

  for (int V : nodeCounts) {
    for (double D : densities) {
      double totalPrimM = 0, totalPrimL = 0;
      double totalKruskalM = 0, totalKruskalL = 0;
      double totalDijkstraM = 0, totalDijkstraL = 0;
      double totalFBM = 0, totalFBL = 0;

      for (int i = 0; i < repetitions; i++) {
        Graph gMST = du.generateGraph(V, (float)D, false);

        if (alg == "PRIM" || alg == "ALL") {
          totalPrimM += SolvingUtility::primMatrix(gMST, 0);
          totalPrimL += SolvingUtility::primList(gMST, 0);
        }
        if (alg == "KRUSKAL" || alg == "ALL") {
          totalKruskalM += SolvingUtility::kruskalMatrix(gMST);
          totalKruskalL += SolvingUtility::kruskalList(gMST);
        }
        Graph gSP = du.generateGraph(V, (float)D, true);
        if (alg == "DIJKSTRA" || alg == "ALL") {
          totalDijkstraM += SolvingUtility::dijkstraMatrix(gSP, 0, V - 1);
          totalDijkstraL += SolvingUtility::dijkstraList(gSP, 0, V - 1);
        }
        if (alg == "FORD_BELLMAN" || alg == "ALL") {
          totalFBM += SolvingUtility::fordBellmanMatrix(gSP, 0, V - 1);
          totalFBL += SolvingUtility::fordBellmanList(gSP, 0, V - 1);
        }
      }

      std::cout << "V: " << V << ", D: " << (int)(D * 100) << "%\n";
      if (alg == "PRIM" || alg == "ALL") {
        std::cout << "  Avg Prim Matrix:      " << totalPrimM / repetitions
                  << " ms\n";
        std::cout << "  Avg Prim List:        " << totalPrimL / repetitions
                  << " ms\n";
      }
      if (alg == "KRUSKAL" || alg == "ALL") {
        std::cout << "  Avg Kruskal Matrix:   " << totalKruskalM / repetitions
                  << " ms\n";
        std::cout << "  Avg Kruskal List:     " << totalKruskalL / repetitions
                  << " ms\n";
      }
      if (alg == "DIJKSTRA" || alg == "ALL") {
        std::cout << "  Avg Dijkstra Matrix:  " << totalDijkstraM / repetitions
                  << " ms\n";
        std::cout << "  Avg Dijkstra List:    " << totalDijkstraL / repetitions
                  << " ms\n";
      }
      if (alg == "FORD_BELLMAN" || alg == "ALL") {
        std::cout << "  Avg Ford-Bell. Matrix:" << totalFBM / repetitions
                  << " ms\n";
        std::cout << "  Avg Ford-Bell. List:  " << totalFBL / repetitions
                  << " ms\n";
      }
      std::cout << "-----------------------------------\n";
    }
  }
}

void runSingleFileTest() {
  DataUtility du;
  std::string filename = Config::testFilename.getValue();
  std::string alg = Config::testAlg.getValue();
  std::cout << "--- Single File Test Mode (" << filename << ") ---\n";

  Config::printAfterSolving.setSetting(true);
  Config::printAfterGenerating.setSetting(true);

  try {

    Graph gMST = du.readGraph(filename, false);
    if (alg == "PRIM" || alg == "ALL") {
      SolvingUtility::primMatrix(gMST, 0);
      SolvingUtility::primList(gMST, 0);
    }
    if (alg == "KRUSKAL" || alg == "ALL") {
      SolvingUtility::kruskalMatrix(gMST);
      SolvingUtility::kruskalList(gMST);
    }

    Graph gSP = du.readGraph(filename, true);
    if (alg == "DIJKSTRA" || alg == "ALL") {
      SolvingUtility::dijkstraMatrix(gSP, 0, gSP.vertices - 1);
      SolvingUtility::dijkstraList(gSP, 0, gSP.vertices - 1);
    }
    if (alg == "FORD_BELLMAN" || alg == "ALL") {
      SolvingUtility::fordBellmanMatrix(gSP, 0, gSP.vertices - 1);
      SolvingUtility::fordBellmanList(gSP, 0, gSP.vertices - 1);
    }
  } catch (...) {
    std::cout << "Error processing file: " << filename << "\n";
  }
}

int main(int argc, char **argv) {
  srand(time(NULL));
  std::string configName = "config.json";
  if (argc > 1)
    configName = argv[1];

  try {
    Config::setConfigFile(configName);
    Config::loadConfigFromFile();
  } catch (const std::exception &e) {
    std::cerr << "Config error: " << e.what() << "\n";
    return 1;
  }

  if (Config::inTestMode.getValue()) {
    runSingleFileTest();
  } else {
    runAutomatedBenchmarking();
  }
  return 0;
}
