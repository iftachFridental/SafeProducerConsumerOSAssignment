//
// Created by Iftach Fridental on 19/01/2018.
//

#ifndef OS4_COEDITOR_H
#define OS4_COEDITOR_H

#include "Dispatcher.h"
#include <chrono>

class CoEditor {

private:
    BoundedBuffer *news_q;
    LockedQueue *screen_q;
    std::thread *t;

public:
    CoEditor(BoundedBuffer *news_q, LockedQueue *screen_q);

    ~CoEditor();

    void start();

    void stop();

    void newsToScreen();

    void edit(News *n);
};

#endif //OS4_COEDITOR_H
