//
// Created by Iftach Fridental on 19/01/2018.
//
#pragma once
#ifndef OS4_DISPATCHER_H
#define OS4_DISPATCHER_H

#include "Producer.h"

class Dispatcher {

private:
    std::queue<Producer> prod_q;
    LockedQueue *types_list[3];
    std::thread *t;

    void sendDones();

public:
    Dispatcher(queue<Producer> &prod_q);

    ~Dispatcher();

    void start();

    void stop();

    void sortNews();

    LockedQueue *getQByType(NewsType t);

};

#endif //OS4_DISPATCHER_H
