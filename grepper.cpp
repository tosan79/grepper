#include "grepper.h"

void Params::parse(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "usage:\n" << "./grepper <string pattern>\n";
        exit(0);
    }
    else if (argc == 2) {
        this->pattern = argv[1];
        this->dir = ".";
        this->log_file = "grepper.log";
        this->result_file = "grepper.txt";
        this->num_of_threads = 4;
    }
    else {
        std::vector<std::string> arguments;
        for (int i = 0; i < argc; i++)
            arguments.push_back(argv[i]);
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