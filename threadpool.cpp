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
        std::unique_lock<std::mutex> lck(mutex);
        data_cond.wait(lck, [this] {
            return !works.empty();
        });
        work = works.front();
        works.pop();
        work();
        if (works.empty()) {
            std::this_thread::yield();
        }
    }
}

void ThreadPool::submit_work(const std::function<void()> work) {
    std::unique_lock<std::mutex> lck(mutex);
    works.push(work);
    data_cond.notify_one();
}

ThreadPool::~ThreadPool() {
    std::unique_lock<std::mutex> lck(mutex);
    is_done = true;
    data_cond.notify_all();
    for (std::thread &t : threads)
        if (t.joinable())
            t.join();
    threads.clear();
}