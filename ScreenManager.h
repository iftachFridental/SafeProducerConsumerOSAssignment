//
// Created by Iftach Fridental on 19/01/2018.
//
#pragma once
#ifndef OS4_SCREENMANAGER_H
#define OS4_SCREENMANAGER_H

#include "LockedQueue.h"
#include <iostream>

class ScreenManager {
private:
    LockedQueue *news_q;
    std::thread *t;

public:
    ScreenManager();

    ~ScreenManager();

    LockedQueue *getScreenQueue();

    void printNews();

    void start();

    void stop();
};

#endif //OS4_SCREENMANAGER_H
