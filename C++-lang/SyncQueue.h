#include <mutex>
#include <condition_variable>
#include <queue>
<<<<<<< HEAD

template <typename T>
class SyncQueue {
public:
    SyncQueue(int capacity) : m_capacity(capacity), m_shutdown(false) {}
    ~SyncQueue() {
        shutdown(); 	// Ensure the destructor of SyncQueue calls shutdown to guarantee all threads are notified before the object is destroyed
    }

    bool push(const T& item) {
        std::unique_lock<std::mutex> lock(mtx);
        if (m_shutdown.load()) {
            return false; // Queue is shutting down, do not push.
        }
        fullQ.wait(lock, [this] { return m_queue.size() < m_capacity || m_shutdown.load(); });
        if (m_shutdown.load()) {
            return false; // Queue is shutting down, do not push.
        }
        m_queue.push(item);
        emptyQ.notify_all(); return true;
=======
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
 
>>>>>>> 281c4a177927d8c3f82a9f0f6eab9c843eaf760b
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mtx);
<<<<<<< HEAD
        if (m_shutdown.load()) {
            throw std::runtime_error("Queue is shutting down");
        }
        emptyQ.wait(lock, [this] { return !m_queue.empty() || m_shutdown.load(); });
        if (m_shutdown.load()) {
            throw std::runtime_error("Queue is shutting down");
        }
        T item = m_queue.front();
        m_queue.pop();
        fullQ.notify_all();
        return item;
    }

    void shutdown() {
        std::unique_lock<std::mutex> lock(mtx);
        m_shutdown.store(true);
        fullQ.notify_all();
        emptyQ.notify_all();
    }

private:
    int m_capacity;
    std::queue<T> m_queue;
    std::mutex mtx;
    std::condition_variable fullQ;
    std::condition_variable emptyQ;
    std::atomic<bool> m_shutdown;
};

// Producer Thread
while (true) {
    T item = generateItem();
    if (!syncQueue.push(item)) {
        break; // Exit loop if push fails due to shutdown.
    }
}

// Consumer Thread
try {
    while (true) {
        T item = syncQueue.pop();
        processItem(item);
    }
} catch (const std::runtime_error& e) {
    // Handle shutdown exception.
    std::cerr << "Consumer exiting: " << e.what() << std::endl;
}

/*
 * Add a joinAll Mechanism
 * If you have control over the threads, consider adding a mechanism to join all threads after signaling shutdown. This ensures that the main thread 
 * waits for all worker threads to finish before proceeding.
 */
=======
        emptyQ.wait(lock, [this] { return container.size() > 0; });
        T item = container.front();
        container.pop();
        lock.unlock();
        fullQ.notify_all();
    }
};
>>>>>>> 281c4a177927d8c3f82a9f0f6eab9c843eaf760b
