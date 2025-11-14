#include "../include/geographic_network.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
#include <functional>

GeographicNetwork::GeographicNetwork() = default;

GeographicNetwork::GeographicNetwork(GeographicNetwork &&other) noexcept : adjList(std::move(other.adjList)) {}
GeographicNetwork &GeographicNetwork::operator=(GeographicNetwork &&other) noexcept
{
    // TODO
    // Impliment the Move assignment operator
}

// --- Vertex Management ---
void GeographicNetwork::addVertex(int node)
{
    // TODO
}

void GeographicNetwork::removeVertex(int node)
{
    // TODO
}

// --- Edge Management ---
void GeographicNetwork::addEdge(int from, int to, int weight)
{
    // TODO
}

void GeographicNetwork::removeEdge(int from, int to)
{
    // TODO
}

// --- Graph Queries ---
bool GeographicNetwork::hasEdge(int from, int to) const
{
    // TODO
    return false;
}

std::vector<int> GeographicNetwork::getAdjacent(int from) const
{
    // TODO
    return {};
}

// --- Core Algorithm: Dijkstra's ---
std::optional<std::vector<int>> GeographicNetwork::findShortestPath(int start, int end) const
{
    // TODO
    return std::nullopt;
}

// --- Core Algorithm: Kruskal's for MST ---
std::vector<GeographicNetwork::MstEdge> GeographicNetwork::calculateMinimumSpanningTree() const
{
    // TODO
    return {};
}

// --- Implementations of Advanced Analysis Functions ---

std::vector<int> GeographicNetwork::findCriticalNodes() const
{
    // TODO
    return {};
}

void GeographicNetwork::findAP_dfs(int u, int &time, std::unordered_map<int, int> &parent, std::unordered_map<int, int> &disc, std::unordered_map<int, int> &low, std::vector<int> &result) const
{
    // TODO
    // This is a helper for find critical nodes, you do not need to write this if you wont be following this certain implimentation
}

std::optional<std::vector<int>> GeographicNetwork::findPathWithMinEffort(int start, int end) const
{
    // TODO
    return {};
}
int GeographicNetwork::findBestCity(int distanceThreshold) const
{
    // TODO
    return -1;
}