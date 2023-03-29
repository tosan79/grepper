#include "threadpool.h"
#include "grepper.h"

//ensures that thread pool is destructed correctly
join_threads::~join_threads()
{
    for(unsigned long i=0;i<threads.size();++i)
    {
        if(threads[i].joinable())
            threads[i].join();
    } 
}

ThreadPool::ThreadPool(int n)
: is_done(false), num_of_threads(n), joiner(threads) {
    try {
        for (int i = 0; i < num_of_threads; i++)
            threads.push_back(std::thread(&ThreadPool::worker, this));    
    } catch(...) {
        is_done = true;
        throw;
    }
}

void ThreadPool::worker() {
    while (!is_done) {
        std::function<void()> work;
        if (works.try_pop(work))
            work();
        else
            std::this_thread::yield();
    }
}

//sends one work (one call of the grep(), for instance) to queue
void ThreadPool::submit_work(const std::function<void()> work) {
    works.push(work);
}

ThreadPool::~ThreadPool() {
    is_done = true;
    //auto stop = std::chrono::high_resolution_clock::now();
}