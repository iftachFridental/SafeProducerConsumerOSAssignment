//
// Created by Ortal Regev and Iftach Fridental on 15/01/2018.
//
#pragma once
#ifndef OS4_PRODUCER_H
#define OS4_PRODUCER_H

#include <thread>
#include <ctime>
#include <cstdlib>
#include "BoundedBuffer.h"

class Producer {

private:
    int prod_id;
    BoundedBuffer* q_;
    int products_num;
    int type_counters[3]; // 0- regular, 1- weather, 2- sports
    std::thread *t;

public:
    Producer(int prod_id, int products_num, int q_capacity);

    ~Producer();

    BoundedBuffer* getQueue(){ return q_; }

    void start();

    void stop();

    News generateRandomNews();

    void insertNews();

};

#endif //OS4_PRODUCER_H
