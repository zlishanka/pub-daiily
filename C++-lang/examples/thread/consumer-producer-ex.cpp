#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>

template<typename T>
class Queue {
    private:
        std::mutex mtx;
        size_t capacity;
        std::condition_variable fullQ;
        std::condition_variable emptyQ;
        std::queue<T> container;
    
    public:
        Queue(int capacity=10): mtx(), capacity(capacity), fullQ(), emptyQ(), container() {}
        ~Queue() {}

        void push(const T& data) {
            std::unique_lock<std::mutex> lock(mtx);
            while (container.size() == capacity) {
                fullQ.wait(lock);
            }
            container.push(data);
            lock.unlock();
            emptyQ.notify_all();
        }

        T pop() {
            std::unique_lock<std::mutex> lock(mtx);
            while (container.size() == 0) {
                emptyQ.wait(lock);
            }
            T data = container.front();
            container.pop();
            lock.unlock();
            fullQ.notify_all();
            return data;
        }
};

Queue<int> bq(1);

void producer(int id) {
    for (int i = 0; i < 10; ++i) {
        bq.push(id*i);
        std::cout << "Procuder ID: " << id << " push " << id*i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void consumer(int id) {
    for (int i = 0; i < 10; ++i) {
        int data = bq.pop();
        std::cout << "Consumer ID: " << id << " pop " << data << std::endl;
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
}

int main() {
    std::thread p1(producer, 1);
    std::thread p2(producer, 2);
    std::thread c1(consumer, 1);
    std::thread c2(consumer, 2);
    
    p1.join(); p2.join(); c1.join(); c2.join();

    return 0;
}