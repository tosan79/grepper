#include "grepper.h"

void Params::parse(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "usage:\n" << "./grepper <string pattern>\n";
        exit(0);
    }
    else if (argc == 2) {
        this->pattern = argv[1];
    }
}

void grep(std::string path, std::string &pattern) {
    std::ifstream ifs(path);
    std::string line;
    std::thread::id tid = std::this_thread::get_id();
    while (std::getline(ifs, line)) {
        if (line.find(pattern) != std::string::npos)
            std::cout << tid << ":" << path << ":" << line << "\n";
    }
}

void enqueue(std::string dir, std::string &pattern, ThreadPool &tp) {
    for (auto x : std::filesystem::recursive_directory_iterator(dir))
        tp.submit_work(std::bind(grep, x.path(), pattern));
}