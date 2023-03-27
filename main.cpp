#include "grepper.h"
#include "threadpool.h"

int main(int argc, char* argv[]) {
    Params ps;
    ps.parse(argc, argv);
    
    ThreadPool tp(3);
    enqueue(".", ps.pattern, tp);

    return 0;
}