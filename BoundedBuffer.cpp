#include "BoundedBuffer.h"

using namespace std;

    BoundedBuffer::BoundedBuffer(int capacity) {
        this->capacity = capacity;
        this->size = 0;
    }

    bool BoundedBuffer::insert(const News &item) {
        if (isFull())
            return false;
        queue_.push(item);
        size++;
        return true;
    }

    bool BoundedBuffer::isFull() {
        return size == capacity;
    }
