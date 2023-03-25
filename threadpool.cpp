#include "threadpool.h"

class ThreadPool {
    bool is_done;
    int num_of_threads;
    std::mutex mutex;
    std::queue<std::function<void()>> works;
    std::vector<std::thread> threads;
    void worker() {
        while (!is_done) {
            std::cout << "working\n";
        }
    }

public:
    ThreadPool(int n)
    : is_done(false), num_of_threads(n) {
        for (int i = 0; i < num_of_threads; i++)
            threads.push_back(std::thread(&ThreadPool::worker, this));
    }
};