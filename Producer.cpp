//
// Created by Iftach Fridental on 19/01/2018.
//

#include "Producer.h"

using namespace std;

class Producer{

public:
    Producer::Producer(int prod_id, int products_num, int q_capacity) {
        this->prod_id = prod_id;
        this->products_num = products_num;
        q_ = new BoundedBuffer(q_capacity);

        this->type_counters = new int[3];
        this->type_counters[0] = 0;
        this->type_counters[1] = 0;
        this->type_counters[2] = 0;

        t = NULL;
        srand(time(nullptr));
    }

    Producer::~Producer() {
        stop();
        delete q_;
        delete[] type_counters;
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
        return new News(type, this->prod_id, type_counters[random_type] - 1);
    }

    void Producer::insertNews() {
        while (products_num > 0) {
            while (q_.isFull()) { ;
            }
            this->q_.lock();
            q_.insert(generateRandomNews());
            this->q_.unlock();
            products_num--;
        }
        this->q_.lock();
        this->q_.insert(new News(DONE, this->prod_id, -1));
        this->q_.unlock();
    }

    void Producer::start() {

        if (t == NULL) {
            t = new thread(insertNews);
        }
    }

    void Producer::stop() {
        if (t != NULL) {
            delete t;
            t = NULL;
        }
    }

};
