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
    auto it = adjList.find(from);
    if (it == adjList.end() || adjList.find(to) == adjList.end()){
        return false; //if either vertex doesnot exist return
    }
    for (int i = 0; i < it->second.size(); i++){
        if (it->second[i] == to){
            return true;
        }
    }
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
    if (start == end){
        return std::vector<int>{start};
    }
    if (adjList.find(start) == adjList.end()){
        return std::nullopt;
    }

    std::queue<int> q;
    std::unordered_map<int, int> parent; //to keep track of what the prev/parent node of each node in our path 
    std::unordered_map<int, bool> visited;

    q.push(start);
    visited[start] = true;
    bool found = false; 
    while (!q.empty() && !found){
        int n = q.front();
        q.pop();

        auto &list = adjList.at(n); //digging into the n node's adjancy list 
        for (int i = 0; i < list.size(); i++){
            if (!visited[list[i]]){
                visited[list[i]] = true;
                parent[list[i]] = n;
                if (list[i] == end){
                    found = true;
                    break;
                }
                q.push(list[i]);
            }
        }
    }
    if (found == false){
        return std::nullopt;
    }

    std::vector<int> bfs;
    int i = end;
    while (i != start){
        bfs.push_back(i);
        i = parent[i]; //basically backtracking i.e u push the end and then u have to push where the end comes from, which is the parent of end and so on
    }
    bfs.push_back(start);
    std::reverse(bfs.begin(), bfs.end());
    return bfs;
}

// --- Advanced Analysis Functions ---

std::vector<std::pair<int, int>> SocialGraph::findEchoChambers() const
{
    // TODO
    std::vector <std::pair<int,int>> mutuals;
    for (auto itA = adjList.begin(); itA!= adjList.end(); ++itA){
        int A = itA->first; //for each user in adjlist we get the people its following to see if they are following a
        for (int i = 0; i <itA->second.size(); i++){
            int B = itA->second[i];
            auto itB = adjList.find(B); //getting iterator to B in adjlist so we can check its following
            int FLAG = 0;
            for (int j = 0; j < itB->second.size(); j++){
                if(itB->second[j] == A){ //if somewhere in following then break means mutual exists
                    FLAG = 1;
                    break;
                }
            }
            if (FLAG == 1){
                if (A < B){ // just a check to make sure duplicates arent added...i.e if 1,2 exists then later it wont add 2,1
                mutuals.push_back({A,B});
                }
            }
        }
    }
    return mutuals;
}

std::unordered_map<int, double> SocialGraph::calculatePageRank(double damping, int iterations) const
{
    // TODO
    return {};
}

std::vector<std::vector<int>> SocialGraph::findCommunities() const
{
    // TODO
    std::vector<std::vector<int>> SCC;
    std::unordered_map<int,bool> visited;
    std::vector<int> finish_stack;
    std::unordered_map<int, std::vector<int>> transposed;

    for (auto it = adjList.begin(); it != adjList.end(); it++) {
        visited[it->first] = false; //no nodes have been visited yet
    }    
    for(auto it = adjList.begin(); it != adjList.end(); ++it){
        if(!visited[it->first]){
            kosaraju_dfs1(it->first,visited,finish_stack);
        }
    }
    for (auto it = adjList.begin(); it != adjList.end(); ++it) {
        transposed[it->first] = std::vector<int>(); // empty vector for nodes with no outgoing edges
    }    
    for (auto it = adjList.begin(); it!=adjList.end(); ++it){
        for (int i = 0; i< it->second.size(); i++){ //loop over neighbors of cur node
            int v = it->second[i]; //one neighbor
            transposed[v].push_back(it->first); //rn in our graph its u->v, now we make it v->u
        }
    }

    for (auto it = visited.begin(); it != visited.end(); ++it) {
        it->second = false; // reset visited
    }
    for (int i = finish_stack.size() - 1; i >= 0; i--) {
        if (!visited[finish_stack[i]]) { //if node hasnt been put in component
            std::vector<int> component;
            kosaraju_dfs2(finish_stack[i], visited, component, transposed);
            SCC.push_back(component); //save this scc
        }
    }
    return SCC;
}

void SocialGraph::kosaraju_dfs1(int u, std::unordered_map<int, bool> &visited, std::vector<int> &finish_stack) const
{
    // TODO
    visited[u] = true;
    auto &list = adjList.at(u);
    for (int i = 0; i < list.size(); i++){
        int v = list[i];
        if(!visited[v]){
            kosaraju_dfs1(v,visited,finish_stack);
        }
    }
    finish_stack.push_back(u);
}

void SocialGraph::kosaraju_dfs2(int u, std::unordered_map<int, bool> &visited, std::vector<int> &component, const std::unordered_map<int, std::vector<int>> &transposed_graph) const
{
    // TODO
    visited[u] = true;
    component.push_back(u);
    auto &transposed = transposed_graph.at(u);
    for (int i = 0; i< transposed.size(); i++){
        int v = transposed[i];
        if(!visited[v]){
            kosaraju_dfs2(v,visited,component,transposed_graph);
        }
    }
}