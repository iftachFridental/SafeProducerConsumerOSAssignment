//
// Created by Iftach Fridental on 19/01/2018.
//
#pragma once
#ifndef OS4_SCREENMANAGER_H
#define OS4_SCREENMANAGER_H

#include "BoundedBuffer.h"
#include <iostream>

class ScreenManager {
private:
    BoundedBuffer *news_q;
    std::thread *t;

public:
    ScreenManager(int capacity);

    ~ScreenManager();

    BoundedBuffer *getScreenQueue();

    void printNews();

    void start();

    void stop();
};

#endif //OS4_SCREENMANAGER_H
