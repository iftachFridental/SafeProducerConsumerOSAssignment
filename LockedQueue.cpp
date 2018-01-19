//
// Created by Iftach Fridental on 19/01/2018.
//

#include "LockedQueue.h"

using namespace std;

LockedQueue::LockedQueue() {
    this->size = 0;
}

News LockedQueue::remove() {
    if (isEmpty()) {
        News *n = new News(regularNews, -1, -1);
        return *n;
    }
    auto item = queue_.front();
    queue_.pop();
    size--;
    return item;
}

bool LockedQueue::insert(const News &item) {
    queue_.push(item);
    size++;
    return true;
}

bool LockedQueue::isEmpty() {
    return size == 0;
}

void LockedQueue::lock() {
    mutex_.lock();
}

void LockedQueue::unlock() {
    mutex_.unlock();
}
