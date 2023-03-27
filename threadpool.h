#ifndef THREADPOOL_INCLUDED
#define THREADPOOL_INCLUDED 1

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <functional>
#include <queue>
#include <condition_variable>

class ThreadPool {
    bool is_done;
    int num_of_threads;
    std::mutex mutex;
    std::condition_variable data_cond;
    std::queue<std::function<void()>> works;
    std::vector<std::thread> threads;
    void worker();

public:
    ThreadPool(int n);
    ~ThreadPool();
    void submit_work(const std::function<void()> work);
};

#endif