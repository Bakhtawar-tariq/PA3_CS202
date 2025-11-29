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
        postToUserEdges.insert(std::make_pair(id,std::vector<Interaction>()));
    }
    else if (type == NodeType::USER){
        userToPostEdges.insert(std::make_pair(id,std::vector<Interaction>()));
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
            for (int j = user_posts.size() - 1; j >= 0; j--){
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
    std::vector<std::pair<int, double>> res;
    //using sets as fastlookup O(1) using count function
    std::unordered_set<int> postids; //interacted posts of target usr

    auto it = userToPostEdges.find(userID);
    for (int i = 0 ; i < it->second.size(); i++){ //basically building all the postids our user has interacted w
        postids.insert(it->second[i].targetID);
    }
    for (auto it2 = userToPostEdges.begin(); it2!= userToPostEdges.end(); ++it2){
        if (it2->first == userID) {
            continue;
        }
        std::unordered_set<int> otherpostids; //interacted posts of otherusers
        int intersectionsize = 0;
        int unionsize = 0;

        for (int i = 0; i < it2->second.size(); i++){
            otherpostids.insert(it2->second[i].targetID); //building postids of the posts a user from the remaining users has interacted w
        }
        for (auto it3 = postids.begin(); it3 != postids.end(); ++it3){ //check posts that our user has iteracted w, and if the other user has also interacted w it then increase intersectionsize
            if(otherpostids.count(*it3)){
                intersectionsize++;
            }
        }
        unionsize = postids.size() + otherpostids.size() - intersectionsize;
        double jaccard = 0.0;
        if (unionsize != 0){ // avoid division by 0
            jaccard = (double)intersectionsize/unionsize;
        }
        if (jaccard > 0.0){
            res.push_back(std::make_pair(it2->first, jaccard));
        }
    }

    //sorting by ascending similarity using bubble sort
    for(int i = 0; i < res.size(); i++){
        for (int j = i+1; j<res.size(); j++){
            if(res[i].second > res[j].second){
                std::pair<int,double> temp = res[i];
                res[i] = res[j];
                res[j] = temp;
            }
        }
    }
    //now for descending reverse the res
    std::vector<std::pair<int,double>> reversed;
    for (int i = res.size()-1; i >= 0; i--){
        reversed.push_back(res[i]);
    }
    if(reversed.size()> topN){ //we need only topN, if less than topN then simply return reversed as it is
        reversed.resize(topN);
    }
    return reversed;
}

std::vector<int> InteractionGraph::recommendPosts(int userID, int topN) const
{
    // This implementation uses the top 5 most similar users to generate recommendations.
    // TODO
    auto similar = findSimilarUsers(userID, 5);
    std::unordered_map<int,double> postscore;
    std::unordered_set<int> alreadyseen; //using set so duplicate posts dont get added + quick search
    
    auto userposts = userToPostEdges.find(userID); //checking if user exists
    if(userposts != userToPostEdges.end()){
        auto interactions = userposts->second; //get posts its interacted w
        for (int i = 0; i < interactions.size(); i++){
            alreadyseen.insert(interactions[i].targetID); //loop through and push them to seen i.e filtering them out
        }
    }
    for (int i = 0; i< similar.size(); i++){//loop through similar users
        auto simposts = userToPostEdges.find(similar[i].first); 
        if(simposts != userToPostEdges.end()){ 
            auto interactions = simposts->second; //find the posts a similar user interacted w
            for (int j = 0; j <interactions.size(); j++){ //loop through a similar users interacted posts
                if (alreadyseen.find(interactions[j].targetID) != alreadyseen.end()){//if the post has been seen by user then skip
                    continue;
                }
                postscore[interactions[j].targetID] += similar[i].second * interactions[j].weight; //calculating score of each post by multiplying its weight with how similar the user is w our og user
            }
        }
    }
    std::vector<std::pair<int,double>> score; //since we need sorted, we convert map to vector 
    for (auto it = postscore.begin(); it != postscore.end(); ++it){
        score.push_back(*it);
    }
    for(int i = 0; i < score.size(); i++){ //bubble sort 
        for (int j = i+1; j<score.size(); j++){
            if(score[i].second > score[j].second){
                std::pair<int,double> temp = score[i];
                score[i] = score[j];
                score[j] = temp;
            }
        }
    }
    std::vector<std::pair<int,double>> reversed; //descending order
    for (int i = score.size()-1; i >= 0; i--){
        reversed.push_back(score[i]);
    }
    std::vector<int> recommend; //need only keys
    for (int i = 0; i < reversed.size(); i++){
        recommend.push_back(reversed[i].first);
    }
    if (recommend.size() > topN){
        recommend.resize(topN);
    }
    return recommend;
}

std::unordered_map<int, double> InteractionGraph::calculateTrendScores(const std::unordered_map<int, double> &pageRanks) const
{
    // TODO: Implement this function to calculate trend scores based on PageRank.
    std::unordered_map<int, double> trends;
    for (auto it = postToUserEdges.begin(); it!= postToUserEdges.end(); ++it){ //iterating thru posts
        double score = 0.0;
        for (int i = 0; i < it->second.size(); i++){ //iterating thru users interacted w the post
            int user = it->second[i].targetID; //extracting each user and weight of interaction
            int weight = it->second[i].weight;

            auto rank = pageRanks.find(user); // find the users rank
            if (rank != pageRanks.end()){ //check if pagerank is empty for user
                score = score + (rank->second * weight); //apply in formula
            }
        }
        trends[it->first] = score; //update score for that post
    }
    return trends;
}

std::optional<std::vector<int>> InteractionGraph::getProcessingOrder() const
{
    // TODO: Implement Kahn's algorithm for topological sorting(aik aur hint lelo).
    return std::nullopt;
}