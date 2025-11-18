#include "SocialMediaSystem.h"

SocialMediaSystem::SocialMediaSystem()
    : feed(10)  // initial capacity
{
}

int SocialMediaSystem::findPostIndex(int value) {
    for (int i = 0; i < feed.size(); i++){
        if (feed.elementAt(i) == value){
            return i;
        }
    }
    return -1;
}

void SocialMediaSystem::buildUndiscoveredFeed(vector<int> likes) {
    for (int i = 0; i < likes.size(); i++){
        feed.insertKey(likes[i]);
    }
}

void SocialMediaSystem::updatePostLikes(int oldLikes, int newLikes) {
    int indx = findPostIndex(oldLikes);
    if (indx == -1){
        return;
    }
    else{
        feed.increaseKey(oldLikes,newLikes);
    }
}

void SocialMediaSystem::clearLowEngagementPosts(int threshold) {
    
}

vector<int> SocialMediaSystem::getTopNPosts(int N) {
    vector<int> topItems;
    return topItems;
}

void SocialMediaSystem::decreasePostLikes(int currentLikes, int newLikes) {
    int indx = findPostIndex(currentLikes);
    if (indx == -1){
        return;
    }
    else{
        feed.decreaseKey(currentLikes,newLikes);
    }
}
