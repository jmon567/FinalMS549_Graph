// graph.cpp

#include "graph.hpp"
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/connected_components.hpp>
#include <iostream>
#include <queue>
#include <algorithm>

TransportGraph createGraph() {
    TransportGraph graph;

    // Add stations (vertices)
    for (int i = 0; i < 20; ++i) {
        auto v = boost::add_vertex(graph);
        graph[v].name = "Station " + std::to_string(i);
    }

    // Define routes (edges) with distances
    std::vector<std::tuple<int, int, double>> routes = {
        {0, 1, 5.0}, {1, 2, 3.2}, {2, 3, 4.5}, {3, 4, 2.1},
        {4, 5, 7.3}, {5, 6, 3.8}, {6, 7, 6.4}, {7, 8, 2.9},
        {8, 9, 5.6}, {9, 10, 4.0}, {10, 11, 6.1}, {11, 12, 3.3},
        {12, 13, 2.7}, {13, 14, 4.8}, {14, 15, 5.2}, {15, 16, 3.0},
        {16, 17, 4.4}, {17, 18, 6.6}, {18, 19, 5.5}, {19, 0, 7.1}
    };

    // Add edges to the graph
    for (const auto& route : routes) {
        auto e = boost::add_edge(std::get<0>(route), std::get<1>(route), graph).first;
        graph[e].distance = std::get<2>(route);
    }

    return graph;
}

void displayGraph(const TransportGraph& graph) {
    std::cout << "Transportation Network:\n";

    auto vertices = boost::vertices(graph);
    for (auto it = vertices.first; it != vertices.second; ++it) {
        std::cout << graph[*it].name << " connects to:\n";

        auto neighbors = boost::adjacent_vertices(*it, graph);
        for (auto nbr = neighbors.first; nbr != neighbors.second; ++nbr) {
            auto edge = boost::edge(*it, *nbr, graph).first;
            std::cout << "  - " << graph[*nbr].name
                << " [Distance: " << graph[edge].distance << " km]\n";
        }
        std::cout << "\n";
    }
}

void findShortestPath(const TransportGraph& graph, int start, int end) {
    std::vector<int> predecessors(boost::num_vertices(graph));
    std::vector<double> distances(boost::num_vertices(graph));

    boost::dijkstra_shortest_paths(
        graph,
        start,
        boost::predecessor_map(&predecessors[0]).distance_map(&distances[0]).
        weight_map(boost::get(&Route::distance, graph))
    );

    // Construct the shortest path
    std::vector<int> path;
    for (int v = end; v != start; v = predecessors[v]) {
        path.push_back(v);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    // Display the shortest path
    std::cout << "\nShortest path from " << graph[start].name
        << " to " << graph[end].name << ":\n";
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << graph[path[i]].name;
        if (i < path.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << "\nTotal distance: " << distances[end] << " km\n";
}

void performBFS(const TransportGraph& graph, int start) {
    std::vector<bool> visited(boost::num_vertices(graph), false);
    std::queue<int> queue;

    visited[start] = true;
    queue.push(start);

    std::cout << "\nBFS starting from " << graph[start].name << ":\n";

    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        std::cout << graph[u].name << "\n";

        auto neighbors = boost::adjacent_vertices(u, graph);
        for (auto nbr = neighbors.first; nbr != neighbors.second; ++nbr) {
            if (!visited[*nbr]) {
                visited[*nbr] = true;
                queue.push(*nbr);
            }
        }
    }
}

void findConnectedComponents(const TransportGraph& graph) {
    std::vector<int> component(boost::num_vertices(graph));
    int num = boost::connected_components(graph, &component[0]);

    std::cout << "\nNumber of connected components: " << num << "\n";

    // Group stations by component
    std::vector<std::vector<std::string>> components(num);
    auto vertices = boost::vertices(graph);
    for (auto it = vertices.first; it != vertices.second; ++it) {
        int comp = component[*it];
        components[comp].push_back(graph[*it].name);
    }

    // Display each component
    for (int i = 0; i < num; ++i) {
        std::cout << "Component " << i + 1 << ":\n";
        for (const auto& station : components[i]) {
            std::cout << "  - " << station << "\n";
        }
    }
}

