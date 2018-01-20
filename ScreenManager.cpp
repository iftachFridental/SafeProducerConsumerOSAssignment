//
// Created by Ortal Regev and Iftach Fridental on 15/01/2018.
//

#include "ScreenManager.h"

using namespace std;

ScreenManager::ScreenManager(int capacity) {
    news_q = new BoundedBuffer(capacity);
    t = nullptr;
}

ScreenManager::~ScreenManager() {
    delete news_q;
    stop();
}

void ScreenManager::printNews() {
    int done_counter = 0;
    while (done_counter < 3) {
        while (news_q->isEmpty()) { ;
        }
        news_q->lock();
        News n = news_q->remove();
        news_q->unlock();
        if (n.getType() == DONE) {
            done_counter++;
            continue;
        }
        cout << n.toString() << endl;
    }
    cout << "Done." << endl;
}

void ScreenManager::start() {
    if (t == nullptr)
        t = new thread(&ScreenManager::printNews, this);
}

void ScreenManager::stop() {
    if (t != nullptr) {
        t->join();
        delete t;
        t = nullptr;
    }
}

BoundedBuffer *ScreenManager::getScreenQueue() {
    return this->news_q;
}

