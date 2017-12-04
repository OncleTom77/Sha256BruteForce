#ifndef ThreadManager_hpp
#define ThreadManager_hpp

#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <thread>
#include <math.h>

#include "utils.hpp"
#include "WordGenerator.hpp"

class ThreadManager {
public:
	ThreadManager(const std::string hashedPassword, const unsigned int nbThread);
	~ThreadManager();
	
private:
	Utils utils;
	WordGenerator generator;
	
	std::deque<std::thread> threads;
	std::chrono::time_point<std::chrono::system_clock> start;
	std::chrono::time_point<std::chrono::system_clock> end;
};

#endif /* ThreadManager_hpp */
