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
    if (type == NodeType::POST){
        postToUserEdges[id];
    }
    else if (type == NodeType::USER){
        userToPostEdges[id];
    }
}

void InteractionGraph::removeVertex(int id, NodeType type)
{
    // TODO: Implement this function. This is the most complex one.
    // If you remove a USER, you must also clean up their interactions from the postToUserEdges map.
    // If you remove a POST, you must do the reverse from the userToPostEdges map
    if (type == NodeType::USER){//remove some user
        std::vector<Interaction>& user_posts = userToPostEdges.at(id); //getting all the posts user has interacted w
        for (int i = 0; i < user_posts.size(); i++){
            int postid = user_posts[i].targetID; //getting post id of each post user has interacted w
            std::vector<Interaction>& post_int = postToUserEdges.at(postid); //getting all the users that interacted w this post (which our user also interacted w)
            for (int j = post_int.size() - 1; j >= 0; j--){ //since erasing so going backwards wont affect indexes before it
                if (post_int[j].targetID == id){ //removing user from that posts interactions
                    post_int.erase(post_int.begin()+j);
                }
            }
        }
        userToPostEdges.erase(id);
    }

    else if( type == NodeType::POST){ //remove some post
        //reversing logic of remove user
        std::vector<Interaction>& post_int = postToUserEdges.at(id); //getting all the users that have interacted w the post
        for (int i = 0; i < post_int.size(); i++){
            int userid = post_int[i].targetID; //getting user id of each user that interacted w the post
            std::vector<Interaction>& user_posts = userToPostEdges.at(userid); //getting all posts of that user which interacted w the post we wanna remove
            for (int j = post_int.size() - 1; j >= 0; j--){
                if (user_posts[j].targetID == id){ //removing the post from each users' interaction
                    user_posts.erase(user_posts.begin()+j);
                }
            }
        }
        postToUserEdges.erase(id);
    }
}

void InteractionGraph::addInteraction(int userID, int postID, int weight)
{
    // TODO: Implement this function.
    // Remember to update BOTH maps to keep them in sync.
    userToPostEdges[userID].push_back({postID, weight});
    postToUserEdges[postID].push_back({userID, weight});
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