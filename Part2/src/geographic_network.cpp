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
    if (this != &other){
        adjList = move(other.adjList);
        other.adjList.clear();
    }
    return *this;
}

// --- Vertex Management ---
void GeographicNetwork::addVertex(int node)
{
    // TODO
    adjList.insert(std::make_pair(node, std::vector<Edge>()));
}

void GeographicNetwork::removeVertex(int node)
{
    // TODO
    adjList.erase(node);
    for (auto it = adjList.begin(); it != adjList.end(); ++it){
        auto& edge = it->second;
        for (int i = edge.size()-1; i >= 0; i--){
            if (edge[i].to == node){
                edge.erase(edge.begin()+i);
            }
        }
    }
}

// --- Edge Management ---
void GeographicNetwork::addEdge(int from, int to, int weight)
{
    // TODO
    if(!adjList.count(from)){
        addVertex(from);
    }
    if(!adjList.count(to)){
        addVertex(to);
    }
    adjList[from].push_back({to,weight});
    adjList[to].push_back({from,weight});
}

void GeographicNetwork::removeEdge(int from, int to)
{
    // TODO
    if (adjList.count(from)){
        auto &edges = adjList.at(from);
        for (int i = edges.size()-1; i >= 0; i--){
            if (edges[i].to == to){
                edges.erase(edges.begin()+i);
            }
        }
    }
    if (adjList.count(to)){
        auto &edges = adjList.at(to);
        for (int i = edges.size()-1; i >= 0; i--){
            if (edges[i].to == from){
                edges.erase(edges.begin()+i);
            }
        }
    }
}

// --- Graph Queries ---
bool GeographicNetwork::hasEdge(int from, int to) const
{
    // TODO
    if(!adjList.count(from)){
        return false;
    }
    auto edges = adjList.at(from);
    for (int i = 0; i<edges.size(); i++){
        if (edges[i].to == to){
            return true;
        }
    }
    return false;
}

std::vector<int> GeographicNetwork::getAdjacent(int from) const
{
    // TODO
    std::vector<int> adjacent;
    if(!adjList.count(from)){
        return adjacent;
    }
    auto edges = adjList.at(from);
    for (int i = 0; i < edges.size(); i++){
        adjacent.push_back(edges[i].to);
    }
    return adjacent;
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