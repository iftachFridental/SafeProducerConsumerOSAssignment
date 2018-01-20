//
// Created by Ortal Regev and Iftach Fridental on 15/01/2018.
//
#pragma once
#ifndef OS4_FLOWMANAGER_H
#define OS4_FLOWMANAGER_H

#include "Dispatcher.h"
#include "ScreenManager.h"
#include "CoEditor.h"
#include <fstream>
#include <sstream>

class FlowManager {
private:
    std::string cfg_file;
    std::queue<Producer> prod_arr;
    Dispatcher *dispacher;
    CoEditor *coEditors[3];
    ScreenManager *screenManager;

    int stringToInt(string integer);

    void startAllProducers();

public:
    FlowManager(std::string cfg_file);

    ~FlowManager();

    void initByCfg();

    void run();

};

#endif //OS4_FLOWMANAGER_H
