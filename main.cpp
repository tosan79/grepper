#include "grepper.h"

class Params {
public:
    std::string pattern;
    std::string dir, log_file, result_file;
    int num_of_threads;

    void parse(int argc, char* argv[]);
};

void Params::parse(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "usage:\n" << "./grepper <string pattern>\n";
        exit(0);
    }
    else if (argc == 2) {
        this->pattern = argv[1];
    }
}

void grep(std::string dir, std::string pattern) {
    std::thread::id tid = std::this_thread::get_id();
    std::cout << "thread id: " << std::dec << tid << "\n";
    for (auto x : std::filesystem::recursive_directory_iterator(dir)) {
        std::ifstream ifs(x.path());
        std::string l;
        while (std::getline(ifs, l)) {
            if (l.find(pattern) != std::string::npos)
                std::cout << x.path() << l << "\n";
        }
    }
}

int main(int argc, char* argv[]) {
    Params ps;
    ps.parse(argc, argv);
    
    std::thread t1(grep, ".", ps.pattern);
    std::thread t2(grep, ".", ps.pattern);
    t1.join();
    t2.join();



    return 0;
}