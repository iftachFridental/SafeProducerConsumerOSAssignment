//
// Created by Ortal Regev and Iftach Fridental on 15/01/2018.
//
#pragma once
#ifndef OS4_COEDITOR_H
#define OS4_COEDITOR_H

#include "BoundedBuffer.h"
#include <chrono>

class CoEditor {

private:
    LockedQueue *news_q;
    BoundedBuffer *screen_q;
    std::thread *t;

public:
    CoEditor(LockedQueue *news_q, BoundedBuffer *screen_q);

    ~CoEditor();

    void start();

    void stop();

    void newsToScreen();

    void edit(News *n);
};

#endif //OS4_COEDITOR_H
