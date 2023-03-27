#ifndef GREPPER_INCLUDED
#define GREPPER_INCLUDED 1

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include "threadpool.h"

class Params {
public:
    std::string pattern;
    std::string dir, log_file, result_file;
    int num_of_threads;

    void parse(int argc, char* argv[]);
};

void grep(std::string path, std::string &pattern);
void enqueue(std::string dir, std::string &pattern, ThreadPool &tp);

#endif