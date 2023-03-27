#include "grepper.h"
#include "threadpool.h"

int main(int argc, char* argv[]) {
    Params ps;
    ps.parse(argc, argv);
    
    ThreadPool tp(4);
    usleep(10000);
    enqueue(".", ps.pattern, tp);
    
    return 0;
}