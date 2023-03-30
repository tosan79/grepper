#ifndef GREPPER_INCLUDED
#define GREPPER_INCLUDED 1

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include "threadpool.h"

class Params {
public:
    std::string pattern;
    std::string dir, log_file, result_file;
    int num_of_threads;

    void parse(int argc, char* argv[]);
};

struct res {
    std::vector<std::string> paths;
    std::vector<int> line_nums;
    std::vector<std::string> lines;
    int counter = 0;
};

bool cmp_log(const std::pair<std::thread::id, unsigned long> &p1, const std::pair<std::thread::id, unsigned long> &p2);
bool cmp_res(const std::pair<std::string, int> &p1, const std::pair<std::string, int> &p2);

void grep(std::string path, std::string &pattern);

#endif