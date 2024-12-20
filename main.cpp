// main.cpp

#include "graph.hpp"
#include <iostream>

int main() {
    // Create the transportation graph
    TransportGraph graph = createGraph();

    // Display the graph's key features
    displayGraph(graph);

    // Implement Dijkstra's algorithm for path-finding
    int startStation = 0;  // Starting from Station 0
    int endStation = 10;   // Destination is Station 10
    findShortestPath(graph, startStation, endStation);

    // Perform Breadth-First Search traversal
    performBFS(graph, startStation);

    // Find connected components in the graph
    findConnectedComponents(graph);

    return 0;
}
