#include "grepper.h"
#include "threadpool.h"

int main(int argc, char* argv[]) {
    Params ps;
    ps.parse(argc, argv);
    
    ThreadPool tp(ps.num_of_threads);

    //enqueue tasks:
    for (auto x : std::filesystem::recursive_directory_iterator(ps.dir))
        tp.submit_work(std::bind(grep, x.path(), ps.pattern));
    
    return 0;
}