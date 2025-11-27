#include "../include/social_graph.h"
#include <queue>
#include <algorithm>
#include <utility>
#include <vector>
#include <stack>

SocialGraph::SocialGraph() = default;

SocialGraph::SocialGraph(SocialGraph &&other) noexcept
    : adjList(std::move(other.adjList))
{
}

SocialGraph &SocialGraph::operator=(SocialGraph &&other) noexcept
{
    // TODO: Impliment the Move assignment operator
    if (this != &other){
        adjList = move(other.adjList);
        other.adjList.clear();
    }
    return *this;
}

// --- Vertex Management ---

void SocialGraph::addVertex(int node)
{
    // TODO
    adjList.insert(std::make_pair(node,std::vector<int>()));
}

void SocialGraph::removeVertex(int node)
{
    // TODO
    adjList.erase(node);
    for (auto it = adjList.begin(); it != adjList.end(); ++it){
        auto& list = it->second;
        for (int i = list.size()-1; i >= 0; i--){
            if (list[i] == node){
                list.erase(list.begin()+i);
            }
        }
    }
}

// --- Edge Management ---

void SocialGraph::addEdge(int from, int to, int /*weight*/)
{
    // TODO
    if (adjList.find(from) == adjList.end() || adjList.find(to) == adjList.end()){
        return; //if either vertex doesnot exist return
    }
    auto it = adjList.find(from);
    auto &temp = it->second;
    int FLAG = 0; //to check for duplicates
    for (int i = 0; i < temp.size(); i++){
        if (temp[i] == to){
            FLAG = 1;
            break;
        }
    }
    if (FLAG == 0){
        temp.push_back(to);
    }
}

void SocialGraph::removeEdge(int from, int to)
{
    // TODO
    auto it = adjList.find(from);
    if (it == adjList.end()){
        return;
    }
    auto &temp = it->second;
    for (int i = temp.size()-1; i >= 0; i--){
        if(temp[i] == to){
            temp.erase(temp.begin()+ i);
        }
    }
}

// --- Graph Queries ---

bool SocialGraph::hasEdge(int from, int to) const
{
    // TODO
    return false;
}

std::vector<int> SocialGraph::getAdjacent(int from) const
{
    // TODO
    auto it = adjList.find(from);
    if (it == adjList.end()){
        return {};
    }
    return it->second;
}

std::optional<std::vector<int>> SocialGraph::findShortestPath(int start, int end) const
{
    // TODO
    //CHECKING SOMETHING
    return std::nullopt;
}

// --- Advanced Analysis Functions ---

std::vector<std::pair<int, int>> SocialGraph::findEchoChambers() const
{
    // TODO
    return {};
}

std::unordered_map<int, double> SocialGraph::calculatePageRank(double damping, int iterations) const
{
    // TODO
    return {};
}

std::vector<std::vector<int>> SocialGraph::findCommunities() const
{
    // TODO
    return {};
}

void SocialGraph::kosaraju_dfs1(int u, std::unordered_map<int, bool> &visited, std::vector<int> &finish_stack) const
{
    // TODO
}

void SocialGraph::kosaraju_dfs2(int u, std::unordered_map<int, bool> &visited, std::vector<int> &component, const std::unordered_map<int, std::vector<int>> &transposed_graph) const
{
    // TODO
}