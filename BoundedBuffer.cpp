#include "BoundedBuffer.h"

using namespace std;

class BoundedBuffer {

public:

    BoundedBuffer::BoundedBuffer(int capacity) {
        this->capacity = capacity;
        this->queue_ = new queue();
        this->size = 0;
    }

    News BoundedBuffer::remove() {
        if (isEmpty())
            return null;
        auto item = queue_.front();
        queue_.pop();
        size--;
        return item;
    }

    bool BoundedBuffer::insert(const News &item) {
        if (isFull())
            return false;
        queue_.push(item);
        size++;
        return true;
    }

    bool BoundedBuffer::isEmpty() {
        return size == 0;
    }

    bool BoundedBuffer::isFull() {
        return size == capacity;
    }

    void BoundedBuffer::lock() {
        mutex_.lock();
    }

    void BoundedBuffer::unlock() {
        mutex_.unlock();
    }

    BoundedBuffer::~BoundedBuffer() {
        delete queue_;
        delete mutex_;
    }


};