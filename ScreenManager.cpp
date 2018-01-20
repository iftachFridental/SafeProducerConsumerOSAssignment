//
// Created by Iftach Fridental on 19/01/2018.
//

#include "ScreenManager.h"

using namespace std;

ScreenManager::ScreenManager() {
    news_q = new LockedQueue();
    t = nullptr;
}

ScreenManager::~ScreenManager() {
    delete news_q;
    stop();
}

void ScreenManager::printNews() {
    int done_counter = 0;
    News *n = nullptr;
    while (done_counter < 3) {
        while (news_q->isEmpty()) { ;
        }
        news_q->lock();
        n = &(news_q->remove());
        news_q->unlock();
        if (n->getType() == DONE) {
            done_counter++;
            continue;
        }
        cout << n->toString() << endl;
    }
    cout << "Done." << endl;
}

void ScreenManager::start() {
    if (t == nullptr)
        t = new thread(printNews);
}

void ScreenManager::stop() {
    if (t != nullptr) {
        delete t;
        t = nullptr;
    }
}

LockedQueue *ScreenManager::getScreenQueue() {
    return this->news_q;
}

