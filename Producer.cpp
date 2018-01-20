//
// Created by Ortal Regev and Iftach Fridental on 15/01/2018.
//

#include "Producer.h"

using namespace std;

    Producer::Producer(int prod_id, int products_num, int q_capacity) {
        this->prod_id = prod_id;
        this->products_num = products_num;
        q_ = new BoundedBuffer(q_capacity);

        this->type_counters[0] = 0;
        this->type_counters[1] = 0;
        this->type_counters[2] = 0;

        t = nullptr;
        srand(time(nullptr));
    }

    Producer::~Producer() {
        stop();
        delete q_;
    }

    News Producer::generateRandomNews() {

        int random_type = rand() % 3;
        NewsType type;
        switch (random_type) {
            case 0:
                type = regularNews;
                break;
            case 1:
                type = weather;
                break;
            case 2:
                type = sports;
                break;
        }
        type_counters[random_type]++;
        News n(type, this->prod_id, type_counters[random_type] - 1);
        return n;
    }

    void Producer::insertNews() {
        while (products_num > 0) {
            while (q_->isFull()) { ; }
            this->q_->lock();
            q_->insert(generateRandomNews());
            this->q_->unlock();
            products_num--;
        }
        while (q_->isFull()) { ; }
        this->q_->lock();
        this->q_->insert(News(DONE, this->prod_id, -1));
        this->q_->unlock();
    }

    void Producer::start() {

        if (t == nullptr) {
            t = new thread(&Producer::insertNews, this);
        }
    }

    void Producer::stop() {
        if (t != nullptr) {
            delete t;
            t = nullptr;
        }
    }
