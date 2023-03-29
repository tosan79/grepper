#include "grepper.h"
#include "threadpool.h"

int main(int argc, char* argv[]) {
    
    //auto start = std::chrono::high_resolution_clock::now();

    //parse program arguments:
    Params ps;
    ps.parse(argc, argv);
    
    //output file streams
    std::ofstream log(ps.log_file);
    std::ofstream res(ps.result_file);

    int searched_files = 0;
    extern int files_with_pattern;
    extern int num_of_patterns;

    //use threads pool:
    ThreadPool tp(ps.num_of_threads);

    //enqueue tasks:
    for (auto x : std::filesystem::recursive_directory_iterator(ps.dir)) {
        if (std::filesystem::is_regular_file(x))
            searched_files++;
        tp.submit_work(std::bind(grep, x.path(), ps.pattern, std::ref(log), std::ref(res)));
    }

    //extern std::chrono::steady_clock::time_point stop;
    //auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    //ending output:
    std::cout << "Searched files: " << searched_files << "\n";
    std::cout << "Files with pattern: " << files_with_pattern << "\n";
    std::cout << "Patterns number: " << num_of_patterns << "\n"; 
    std::cout << "Result file: " << ps.result_file << "\n"; 
    std::cout << "Log file: " << ps.log_file << "\n"; 
    std::cout << "Used threads: " << ps.num_of_threads << "\n";
    //std::cout << "Elapsed time: " << time_elapsed.count() << " [ms]\n"; // <time elapsed from beginning to the end of the program>

    return 0;
}