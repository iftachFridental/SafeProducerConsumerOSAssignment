//
// Created by Iftach Fridental on 19/01/2018.
//

#include "CoEditor.h"

CoEditor::CoEditor(LockedQueue *news_q, BoundedBuffer *screen_q) {
    this->news_q = news_q;
    this->screen_q = screen_q;
    t = nullptr;
}

CoEditor::~CoEditor() {
    stop();
}

void CoEditor::newsToScreen() {
    bool is_done = false;
    while (!is_done) {
        while (news_q->isEmpty()) { ;
        }
        news_q->lock();
        News n = news_q->remove();
        news_q->unlock();
        if (n.getType() == DONE)
            is_done = true;
        else
            edit(&n);
        while (screen_q->isFull()){ ; }
        screen_q->lock();
        screen_q->insert(n);
        screen_q->unlock();
    }
}

void CoEditor::start() {
    if (t == nullptr) {
        t = new thread(&CoEditor::newsToScreen, this);
    }
}

void CoEditor::stop() {
    if (t != nullptr) {
        delete t;
        t = nullptr;
    }
}

void CoEditor::edit(News *n) {
    chrono::milliseconds x(100);
    this_thread::sleep_for(x);
}