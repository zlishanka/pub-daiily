#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <atomic>

template <typename T>
class SyncQueue {

private:
    std::queue<T> container;
    std::mutex mtx;
    std::condition_variable fullQ, emptyQ;
    int capacity;

public:
    SyncQueue(int size) : capacity(size) fullQ(), emptyQ() {}

    void push(T& item) {
        std::unique_lock<std::mutex> lock(mtx);
        fullQ.wait(lock, [this] { return container.size() < capacity; });
        container.push(item);
        lock.unlock();
        emptyQ.notify_all();
 
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mtx);
        emptyQ.wait(lock, [this] { return container.size() > 0; });
        T item = container.front();
        container.pop();
        lock.unlock();
        fullQ.notify_all();
    }
};