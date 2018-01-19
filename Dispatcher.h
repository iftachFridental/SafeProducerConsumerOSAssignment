//
// Created by Iftach Fridental on 19/01/2018.
//

#ifndef OS4_DISPATCHER_H
#define OS4_DISPATCHER_H

#include "Producer.h"

class Dispatcher {

private:
    std::queue<Producer> prod_q;
    BoundedBuffer *types_list[];
    std::thread *t;

    void sendDones();

public:
    Dispatcher(queue<Producer> &prod_q, int buf_size);

    ~Dispatcher();

    void start();

    void stop();

    void sortNews();

};

#endif //OS4_DISPATCHER_H
