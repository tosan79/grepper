#include "grepper.h"
#include "threadpool.h"

int main(int argc, char* argv[]) {
    //start measuring time
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    //parse program arguments:
    Params ps;
    ps.parse(argc, argv);
    
    //output file streams
    std::ofstream logstream(ps.log_file);
    std::ofstream resstream(ps.result_file);

    //results (numbers)
    int searched_files = 0;
    extern int files_with_pattern;
    extern int num_of_patterns;

    //use threads pool:
    ThreadPool tp(ps.num_of_threads);

    //enqueue tasks:
    for (auto x : std::filesystem::recursive_directory_iterator(ps.dir)) {
        if (std::filesystem::is_regular_file(x))
            searched_files++;
        tp.submit_work(std::bind(grep, x.path(), ps.pattern));
    }

    //necessary break for the threads pool to process all tasks on queue
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    //stop measuring time
    std::chrono::high_resolution_clock::time_point stop = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    //logs are in log_map
    extern std::unordered_map<std::thread::id, std::vector<std::string>> log_map;
    
    //sorting by number of files each thread found the pattern in
    std::vector<std::pair<std::thread::id, unsigned long>> lv;
    for (auto &p : log_map)
        lv.push_back(std::make_pair(p.first, p.second.size()));
    std::sort(lv.begin(), lv.end(), cmp_log);
    
    //printing to the log file
    for (auto const &x : lv) {
        logstream << x.first << ": ";
        for (auto const &it : log_map[x.first])
            logstream << it << ", ";
        logstream << "\n";
    }

    //results are in res_map
    extern std::unordered_map<std::string, struct res> res_map;

    //sorting by number of patterns found in each file
    std::vector<std::pair<std::string, unsigned long>> rv;
    for (auto &p : res_map)
        rv.push_back(std::make_pair(p.first, p.second.counter));
    std::sort(rv.begin(), rv.end(), cmp_res);

    //printing to the result file
    for (auto const &x : rv) {
        struct res r = res_map[x.first];
        for (unsigned long i = 0; i < r.paths.size(); i++)
            resstream << r.paths[i] << ":" << r.line_nums[i] << ": " << r.lines[i] << "\n";
    }

    //ending output:
    std::cout << "Searched files: " << searched_files << "\n";
    std::cout << "Files with pattern: " << files_with_pattern << "\n";
    std::cout << "Patterns number: " << num_of_patterns << "\n"; 
    std::cout << "Result file: " << ps.result_file << "\n"; 
    std::cout << "Log file: " << ps.log_file << "\n"; 
    std::cout << "Used threads: " << ps.num_of_threads << "\n";
    std::cout << "Elapsed time: " << time_elapsed.count() << " [ms]\n";

    return 0;
}