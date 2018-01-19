//
// Created by Iftach Fridental on 19/01/2018.
//

#ifndef OS4_BOUNDEDBUFFER_H
#define OS4_BOUNDEDBUFFER_H

#include <queue>
#include <thread>
#include <mutex>
#include <string>
#include <condition_variable>
#include "News.h"

using namespace std;

class BoundedBuffer {
private:
    int size;
    int capacity;
    queue<News> queue_;
    mutex mutex_;

public:
    BoundedBuffer(int size);

    ~BoundedBuffer();

    News remove();

    bool insert(const News &item);

    bool isEmpty();

    void lock();

    void unlock();

    bool isFull();
};

#endif //OS4_BOUNDEDBUFFER_H
