#pragma once
// graph.hpp

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <boost/graph/adjacency_list.hpp>
#include <string>
#include <vector>

// Define vertex properties
struct Station {
    std::string name;
};

// Define edge properties
struct Route {
    double distance;
};

// Define the graph using Boost adjacency_list
typedef boost::adjacency_list<
    boost::vecS,               // OutEdgeList
    boost::vecS,               // VertexList
    boost::undirectedS,        // Directed
    Station,                   // VertexProperties
    Route                      // EdgeProperties
> TransportGraph;

// Function prototypes
TransportGraph createGraph();
void displayGraph(const TransportGraph& graph);
void findShortestPath(const TransportGraph& graph, int start, int end);
void performBFS(const TransportGraph& graph, int start);
void findConnectedComponents(const TransportGraph& graph);

#endif // GRAPH_HPP
