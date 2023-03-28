#include "grepper.h"

//parse program arguments
void Params::parse(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "usage:\n" << "./grepper <string pattern>\n";
        exit(0);
    }

    // default parameters values
    this->pattern = argv[1];
    this->dir = ".";
    this->log_file = "grepper.log";
    this->result_file = "grepper.txt";
    this->num_of_threads = 4;

    int i = 2;
    while (i < argc) {
        if (!std::strcmp(argv[i], "-d") || !std::strcmp(argv[i], "--dir")) {
            this->dir = argv[i+1];
            i += 2;
        }
        if (!std::strcmp(argv[i], "-t") || !std::strcmp(argv[i], "--threads")) {
            this->dir = argv[i+1];
            i += 2;
        }
        if (!std::strcmp(argv[i], "-l") || !std::strcmp(argv[i], "--dir")) {
            this->dir = argv[i+1];
            i += 2;
        }
        if (!std::strcmp(argv[i], "-r") || !std::strcmp(argv[i], "--dir")) {
            this->dir = argv[i+1];
            i += 2;
        }
        /*
        std::string mod = std::string(argv[i]);
        if (mod.compare("-d") || mod.compare("--dir"))
            this->dir = std::string(argv[i+1]);
        else if (mod.compare("-l") || mod.compare("--log_file"))
            this->log_file = std::string(argv[i+1]);
        else if (mod.compare("-r") || mod.compare("--result_file"))
            this->result_file = std::string(argv[i+1]);
        else if (mod.compare("-t") || mod.compare("--threads"))
            this->num_of_threads = std::atoi(argv[i+1]);
        else {
            std::cout << "usage:\n" << "grepper <string pattern>\n";
            std::cout << "optional parameters:\n" << "-d (--dir) <start directory>\n";
            std::cout << "-l (--log_file) <log file>\n" << "-r (--result_file) <result file>\n";
            std::cout << "-t (--threads) <number of threads in the pool>\n";
            exit(0);
        }*/
    }
}

//do a search for the pattern in a specific file
void grep(std::string path, std::string &pattern) {
    std::ifstream ifs(path);
    std::string line;
    std::thread::id tid = std::this_thread::get_id();
    while (std::getline(ifs, line)) {
        if (line.find(pattern) != std::string::npos)
            std::cout << tid << ":" << path << ":" << line << "\n";
    }
}