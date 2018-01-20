//
// Created by Iftach Fridental on 19/01/2018.
//
#pragma once
#ifndef OS4_BOUNDEDBUFFER_H
#define OS4_BOUNDEDBUFFER_H

#include "LockedQueue.h"

using namespace std;

class BoundedBuffer : public LockedQueue {
private:
    int capacity;


public:
    BoundedBuffer(int capacity);

    virtual ~BoundedBuffer() { ; }
    bool insert(const News &item);

    bool isFull();
};

#endif //OS4_BOUNDEDBUFFER_H
