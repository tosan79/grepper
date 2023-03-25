#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>

#include <vector>
#include <functional>
#include <queue>

class Params;
class ThreadPool;
void grep(std::string s, std::string p);