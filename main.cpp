#include "grepper.h"
#include "threadpool.h"

int main(int argc, char* argv[]) {
    
    //parse program arguments:
    Params ps;
    ps.parse(argc, argv);
    std::cout << ps.dir << " " << ps.log_file << " " << ps.result_file << " " << ps.num_of_threads << "\n";
    
    //use threads pool:
    ThreadPool tp(ps.num_of_threads);

    //enqueue tasks:
    for (auto x : std::filesystem::recursive_directory_iterator(ps.dir))
        tp.submit_work(std::bind(grep, x.path(), ps.pattern));
    
    return 0;
}