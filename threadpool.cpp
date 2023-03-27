#include "threadpool.h"
#include "grepper.h"

ThreadPool::ThreadPool(int n)
: is_done(false), num_of_threads(n) {
    for (int i = 0; i < num_of_threads; i++)
        threads.push_back(std::thread(&ThreadPool::worker, this));    
}

void ThreadPool::worker() {
    while (!is_done) {
        std::function<void()> work;
        std::unique_lock<std::mutex> lock(mutex);
        data_cond.wait(lock, [this] { return !works.empty(); });
        if (!works.empty()) {
            work = works.front();
            works.pop();
            work();
        }
    }
}

void ThreadPool::submit_work(const std::function<void()> work) {
    std::unique_lock<std::mutex> lock(mutex);
    works.push(work);
    data_cond.notify_one();
}

ThreadPool::~ThreadPool() {
    std::unique_lock<std::mutex> lock(mutex);
    is_done = true;
    data_cond.notify_all();
    for (unsigned long i = 0; i < threads.size(); i++)
        if (threads[i].joinable())
            threads[i].join();
}