#pragma once

#include <iostream>
#include <assert.h>
#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class BlockingQueue
{
public:
    BlockingQueue(int max_cap = 100)
        :mtx(), fullQ(), emptyQ(), capacity(max_cap) { }

    void push(const T& data) {
        std::unique_lock<std::mutex> lock(mtx);
        while(container.size() == capacity) {
            fullQ.wait(lock );
        }

        assert(container.size() < capacity);
        container.push(data);
        emptyQ.notify_all();
    }


    bool try_push(const T& data) {
        std::unique_lock<std::mutex> lock(mtx);
        if( container.size() < capacity) {
            container.push(data);
            emptyQ.notify_all();
            return 0;
        }
        return 1;
    }


    T pop() {
        std::unique_lock<std::mutex> lock(mtx);
        while(container.empty()) {
            emptyQ.wait(lock );
        }

        assert(!container.empty());
        T front(container.front());
        container.pop();
        fullQ.notify_all();
        return front;
    }

    bool try_pop(T &item ) {
        std::unique_lock<std::mutex> lock(mtx);

        T dummy;
        if( container.empty()) {
            item = dummy;
            return 1;
        }

        item = container.front();
        container.pop();
        fullQ.notify_all();
        return 0;
    }


    T front() {
        std::unique_lock<std::mutex> lock(mtx);
        while(container.empty()) {
            emptyQ.wait(lock );
        }

        assert(!container.empty());
        T front(container.front());
        return front;
    }

    T back() {
        std::unique_lock<std::mutex> lock(mtx);
        while(container.empty()) {
            emptyQ.wait(lock );
        }

        assert(!container.empty());
        T back(container.back());
        return back;
    }

    size_t size() {
        std::lock_guard<std::mutex> lock(mtx);
        return container.size();
    }

    bool empty() {
        std::unique_lock<std::mutex> lock(mtx);
        return container.empty();
    }

    void setCapacity(const size_t cap) {
        capacity = cap;
    }

    int getCapacity() const {
        return capacity;
    }

    void clear()
    {
        std::unique_lock<std::mutex> lock(mtx);
        std::queue<T> emptyQ;
        std::swap(container, emptyQ);
        emptyQ.notify_all();
    }

    void unblock()
    {
        std::unique_lock<std::mutex> lock(mtx);

        if (container.size() == 0) {
            T item;
            container.push(item);
            emptyQ.notify_all();
            return;
        }

        if (container.size() == capacity) {
            container.pop();
            fullQ.notify_all();
        }
    }

private:
    //DISABLE_COPY_AND_ASSIGN(BlockingQueue);
    BlockingQueue(const BlockingQueue& rhs) = delete;
    BlockingQueue(BlockingQueue&& rhs) = delete;
    BlockingQueue& operator= (const BlockingQueue& rhs) = delete;
    BlockingQueue& operator= (BlockingQueue&& rhs) = delete;

private:
    mutable std::mutex mtx;
    std::condition_variable fullQ;
    std::condition_variable emptyQ;
    std::queue<T> container;
    size_t capacity;
};
