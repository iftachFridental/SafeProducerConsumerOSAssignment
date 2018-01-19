//
// Created by Iftach Fridental on 19/01/2018.
//

#include "CoEditor.h"

CoEditor::CoEditor(BoundedBuffer *news_q, LockedQueue *screen_q) {
    this->news_q = news_q;
    this->screen_q = screen_q;
    t = nullptr;
}

CoEditor::~CoEditor() {
    stop();
}

void CoEditor::newsToScreen() {
    bool is_done = false;
    News *n = nullptr;
    while (!is_done) {
        while (news_q->isEmpty()) { ;
        }
        news_q->lock();
        n = &(news_q->remove());
        news_q->unlock();
        if (n->getType() == DONE)
            is_done = true;
        else
            edit(n);
        screen_q->lock();
        screen_q->insert(*n);
        screen_q->unlock();
    }
}

void CoEditor::start() {
    if (t == nullptr) {
        t = new thread(newsToScreen);
    }
}

void CoEditor::stop() {
    if (t != nullptr) {
        delete t;
        t = nullptr;
    }
}

void CoEditor::edit(News *n) {
    this_thread::sleep_for(chrono::milisecond(100));
}