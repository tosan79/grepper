#ifndef GREPPER_INCLUDED
#define GREPPER_INCLUDED 1

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>

class Params;
void grep(std::string s, std::string p);

#endif