//
// Created by Ortal Regev and Iftach Fridental on 15/01/2018.
//

#include "Dispatcher.h"

using namespace std;

Dispatcher::Dispatcher(queue<Producer> &prod_q) {
    this->prod_q = prod_q;
    this->t = nullptr;

    this->types_list[0] = new LockedQueue();
    this->types_list[1] = new LockedQueue();
    this->types_list[2] = new LockedQueue();
}

Dispatcher::~Dispatcher() {
    stop();
    delete types_list[0];
    delete types_list[1];
    delete types_list[2];
}

void Dispatcher::start() {
    if (t == nullptr) {
        t = new thread(&Dispatcher::sortNews, this);
    }
}

void Dispatcher::stop() {
    if (t != nullptr) {
        delete t;
        t = nullptr;
    }
}

void Dispatcher::sortNews() {
    Producer *p = nullptr;
    BoundedBuffer *buf = nullptr;
    while (!prod_q.empty()) {
        p = &(prod_q.front());
        prod_q.pop();
        buf = p->getQueue();
        if (buf->isEmpty()) {
            prod_q.push(*p);
            continue;
        }
        buf->lock();
        News n = buf->remove();
        buf->unlock();

        int type_ind = -1;
        switch (n.getType()) {
            case regularNews:
                type_ind = 0;
                break;
            case weather:
                type_ind = 1;
                break;
            case sports:
                type_ind = 2;
                break;
            case DONE:
                delete p;
                p = nullptr;
                continue;
        }

        types_list[type_ind]->lock();
        types_list[type_ind]->insert(n);
        types_list[type_ind]->unlock();
        prod_q.push(*p);
    }
    sendDones();
}

void Dispatcher::sendDones() {
    for (LockedQueue *q : types_list) {
        q->lock();
        q->insert(News(DONE, -1, -1));
        q->unlock();
    }
}

LockedQueue *Dispatcher::getQByType(NewsType t) {

    int type_ind = -1;
    switch (t) {
        case regularNews:
            type_ind = 0;
            break;
        case weather:
            type_ind = 1;
            break;
        case sports:
            type_ind = 2;
            break;
        case DONE:
            return nullptr;
    }
    return types_list[type_ind];

}