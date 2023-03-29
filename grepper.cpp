#include "grepper.h"

void Params::parse(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "usage:\n" << "./grepper <string pattern>\n";
        exit(0);
    }

    this->pattern = argv[1];
    this->dir = ".";
    this->log_file = "grepper.log";
    this->result_file = "grepper.txt";
    this->num_of_threads = 4;

    for (int i = 2; i < argc; i += 2) {
        if (std::strcmp(argv[i], "-d") == 0 || std::strcmp(argv[i], "--dir") == 0)
            this->dir = argv[i+1];
        else if (std::strcmp(argv[i], "-t")  == 0 || std::strcmp(argv[i], "--threads") == 0)
            this->num_of_threads = std::atoi(argv[i+1]);
        else if (std::strcmp(argv[i], "-l")  == 0 || std::strcmp(argv[i], "--dir") == 0)
            this->log_file = argv[i+1];
        else if (std::strcmp(argv[i], "-r")  == 0 || std::strcmp(argv[i], "--dir") == 0)
            this->result_file = argv[i+1];
        else {
            std::cout << "usage:\n" << "grepper <string pattern>\n";
            std::cout << "optional parameters:\n" << "-d (--dir) <start directory>\n";
            std::cout << "-l (--log_file) <log file>\n" << "-r (--result_file) <result file>\n";
            std::cout << "-t (--threads) <number of threads in the pool>\n";
            exit(0);
        }
    }
}

int files_with_pattern = 0;
int num_of_patterns = 0;

std::mutex fwp_mut;
std::mutex nop_mut;

void grep(std::string path, std::string &pattern, std::ofstream &log, std::ofstream &res) {
    std::ifstream ifs(path);
    std::string::size_type p = path.rfind("/");
    std::string filename = path.substr(p+1);
    std::string line;
    int line_num = 0;
    std::thread::id tid = std::this_thread::get_id();
    bool pat_found = false;
    while (std::getline(ifs, line)) {
        line_num++;
        if (line.find(pattern) != std::string::npos) {
            {
                std::scoped_lock<std::mutex> lock(nop_mut);
                num_of_patterns++;
            }
            if (!pat_found)
                pat_found = true;
            log << tid << ": " << filename << "\n";
            res << path << ":" << line_num << ": " << line << "\n";
        }
    }
    if (pat_found) {
        std::scoped_lock<std::mutex> lock(fwp_mut);
        files_with_pattern++;
    }
}