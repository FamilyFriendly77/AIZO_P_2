#include "Graph.hpp"
#include <iostream>
#include <iomanip>

void Graph::printGraph() {
    std::cout << "\nAdjacency Matrix:\n";
    std::cout << "    ";
    for (int i = 0; i < vertices; i++) std::cout << std::setw(3) << i << " ";
    std::cout << "\n";
    for (int i = 0; i < vertices; i++) {
        std::cout << std::setw(3) << i << "|";
        for (int j = 0; j < vertices; j++) {
            std::cout << std::setw(3) << adjacencyMatrix[i * vertices + j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nAdjacency List:\n";
    for (int i = 0; i < vertices; i++) {
        std::cout << i << ": ";
        for (int j = 0; j < neighbourListSizes[i]; j++) {
            std::cout << "[" << neighbourList[i][j].destination << ", w:" << neighbourList[i][j].weight << "] ";
        }
        std::cout << "\n";
    }
}
