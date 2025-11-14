#include "../include/interaction_graph.h"
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <queue>

InteractionGraph::InteractionGraph() = default;

InteractionGraph::InteractionGraph(InteractionGraph &&other) noexcept
    : userToPostEdges(std::move(other.userToPostEdges)),
      postToUserEdges(std::move(other.postToUserEdges)) {}

InteractionGraph &InteractionGraph::operator=(InteractionGraph &&other) noexcept
{
    if (this != &other)
    {
        userToPostEdges = std::move(other.userToPostEdges);
        postToUserEdges = std::move(other.postToUserEdges);
    }
    return *this;
}

// --- Graph Management ---

void InteractionGraph::addVertex(int id, NodeType type)
{
    // TODO
}

void InteractionGraph::removeVertex(int id, NodeType type)
{
    // TODO: Implement this function. This is the most complex one.
    // If you remove a USER, you must also clean up their interactions from the postToUserEdges map.
    // If you remove a POST, you must do the reverse from the userToPostEdges map
}

void InteractionGraph::addInteraction(int userID, int postID, int weight)
{
    // TODO: Implement this function.
    // Remember to update BOTH maps to keep them in sync.
}

// --- Advanced Analysis Functions ---

std::vector<std::pair<int, double>> InteractionGraph::findSimilarUsers(int userID, int topN) const
{
    // TODO: Implement this function to calculate Jaccard Similarity(issay direct hint kiya doon ).
    return {};
}

std::vector<int> InteractionGraph::recommendPosts(int userID, int topN) const
{
    // This implementation uses the top 5 most similar users to generate recommendations.
    // TODO
    return {};
}

std::unordered_map<int, double> InteractionGraph::calculateTrendScores(const std::unordered_map<int, double> &pageRanks) const
{
    // TODO: Implement this function to calculate trend scores based on PageRank.
    return {};
}

std::optional<std::vector<int>> InteractionGraph::getProcessingOrder() const
{
    // TODO: Implement Kahn's algorithm for topological sorting(aik aur hint lelo).
    return std::nullopt;
}