//
// Created by Iftach Fridental on 19/01/2018.
//

#include "Dispatcher.h"

using namespace std;

Dispatcher::Dispatcher(queue<Producer> &prod_q, int buf_size) {
    this->prod_q = prod_q;
    this->t = nullptr;

    this->types_list[0] = new BoundedBuffer(buf_size);
    this->types_list[1] = new BoundedBuffer(buf_size);
    this->types_list[2] = new BoundedBuffer(buf_size);
}

Dispatcher::~Dispatcher() {
    stop();
    delete[] types_list;
}

void Dispatcher::start() {
    if (t == nullptr) {
        t = new thread(sortNews);
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
    News *n;
    while (!prod_q.empty()) {
        p = &(prod_q.front());
        prod_q.pop();
        buf = p->getQueue();
        if (buf->isEmpty()) {
            prod_q.push(*p);
            continue;
        }
        buf->lock();
        n = &(buf->remove());
        buf->unlock();

        int type_ind = -1;
        switch (n->getType()) {
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

        while (types_list[type_ind]->isFull()) { ;
        }
        types_list[type_ind]->lock();
        types_list[type_ind]->insert(*n);
        types_list[type_ind]->unlock();
        prod_q.push(*p);
    }
    sendDones();
}

void Dispatcher::sendDones() {
    for (BoundedBuffer *q : types_list) {
        while (q->isFull()) { ;
        }
        q->lock();
        q->insert(News(DONE, -1, -1));
        q->unlock();
    }
}

BoundedBuffer *Dispatcher::getQByType(NewsType t) {

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