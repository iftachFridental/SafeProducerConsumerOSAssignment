//
// Created by Ortal Regev and Iftach Fridental on 15/01/2018.
//

#include "FlowManager.h"

using namespace std;

FlowManager::FlowManager(string cfg_file) {
    this->cfg_file = cfg_file;
}

FlowManager::~FlowManager() {
    delete dispacher;
    delete coEditors[0];
    delete coEditors[1];
    delete coEditors[2];
    delete screenManager;
}

void FlowManager::run() {
    initByCfg();
    screenManager = new ScreenManager();
    coEditors[0] = new CoEditor(this->dispacher->getQByType(regularNews), screenManager->getScreenQueue());
    coEditors[1] = new CoEditor(this->dispacher->getQByType(weather), screenManager->getScreenQueue());
    coEditors[2] = new CoEditor(this->dispacher->getQByType(sports), screenManager->getScreenQueue());
    startAllProducers();
    this->dispacher->start();
    coEditors[0]->start();
    coEditors[1]->start();
    coEditors[2]->start();
    screenManager->start();
}

void FlowManager::initByCfg() {
    ifstream infile(this->cfg_file);
    string line = "";
    while (getline(infile, line)) {
        if (line == "")
            continue;
        else if (line.find("PRODUCER ") != string::npos) {
            int prod_id = stringToInt(line.substr(line.find("PRODUCER "), line.length() - 1));
            getline(infile, line);
            int num_of_products = stringToInt(line);
            getline(infile, line);
            int q_size = stringToInt(line.substr(line.find("queue size = "), line.length() - 1));
            Producer *p = new Producer(prod_id, num_of_products, q_size);
            prod_arr.push(*p);
        } else if (line.find("Co-Editor queue size = ") != string::npos) {
            int coEditors_q_size = stringToInt(line.substr(line.find("Co-Editor queue size = "), line.length() - 1));
            dispacher = new Dispatcher(prod_arr, coEditors_q_size);
        } else
            continue;
    }
}

int FlowManager::stringToInt(string integer) {
    stringstream s(integer);
    int x = -1;
    s >> x;
    return x;
}

void FlowManager::startAllProducers() {
    int i = 0;
    Producer *p = nullptr;
    for (i = 0; i < prod_arr.size(); i++) {
        p = &(prod_arr.front());
        prod_arr.pop();
        prod_arr.push(*p);
        p->start();
    }
}