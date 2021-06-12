#include "h2xvideo/cache/router_cache.h"

RouterCache::RouterCache() : max_count_(15){

}

RouterCache::~RouterCache() {

}

bool RouterCache::pushBack(QString pageName, QString pageParam) {
    if (pageName.isEmpty()) {
        return false;
    }

    this->OnReCal();

    RouterNode node(pageName, pageParam);
    list_.push_back(node);
    return true;
}

void RouterCache::OnReCal() {
    if (max_count_ <= 0) {
        max_count_ = 15; // Ä¬ÈÏ15¸ö
    }
    if (list_.size() >= max_count_) {
        int count = (int)(max_count_ / 4 * 3);
        while (list_.size() > count) {
            list_.pop_front();
        }
    }
}

bool RouterCache::peekFront(RouterNode& node) {
    if (this->isEmpty()) {
        return false;
    }

    node = list_.front();
    return true;
}

bool RouterCache::popFront(RouterNode& node) {
    if (this->isEmpty()) {
        return false;
    }

    node = list_.front();
    list_.pop_front();
    return true;
}