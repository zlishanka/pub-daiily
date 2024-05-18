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
    :mtx(), full_(), empty_(), capacity_(max_cap) { }

    void push(const T& data){
        std::unique_lock<std::mutex> lock(mtx);
        while(queue_.size() == capacity_){
            full_.wait(lock );
        }

        assert(queue_.size() < capacity_);
        queue_.push(data);
        empty_.notify_all(); 
    }

    T pop(){
        std::unique_lock<std::mutex> lock(mtx);
        while(queue_.empty()){
            empty_.wait(lock );
        }

        assert(!queue_.empty());
        T front(queue_.front());
        queue_.pop();
        full_.notify_all();
        return front;
    }

    T front(){
        std::unique_lock<std::mutex> lock(mtx);
        while(queue_.empty()){
            empty_.wait(lock );
        }

        assert(!queue_.empty());
        T front(queue_.front());
        return front;
    }

    T back(){
        std::unique_lock<std::mutex> lock(mtx);
        while(queue_.empty()){
            empty_.wait(lock );
        }

        assert(!queue_.empty());
        T back(queue_.back());
        return back;
    }

    size_t size(){
        std::lock_guard<std::mutex> lock(mtx);
        return queue_.size();
    }

    bool empty(){
        std::unique_lock<std::mutex> lock(mtx);
        return queue_.empty();
    }

    void setCapacity(const size_t cap){
        capacity_ = cap;
    }

    int getCapacity() const { return capacity_; }

    void clear() 
    {
        std::unique_lock<std::mutex> lock(mtx);
	std::queue<T> emptyQ;
	std::swap(queue_, emptyQ);
    }

private:
    //DISABLE_COPY_AND_ASSIGN(BlockingQueue);
    BlockingQueue(const BlockingQueue& rhs);
    BlockingQueue& operator= (const BlockingQueue& rhs);

private:
    mutable std::mutex mtx;
    std::condition_variable full_;
    std::condition_variable empty_;
    std::queue<T> queue_;
    size_t capacity_; 
};

