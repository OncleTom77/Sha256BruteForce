//
//  ThreadManager.hpp
//  sha256BruteForce
//
//  Created by Thomas Fouan on 15/10/2017.
//  Copyright © 2017 Thomas Fouan. All rights reserved.
//

#ifndef ThreadManager_hpp
#define ThreadManager_hpp

#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <thread>

#include "utils.hpp"
#include "combinations.hpp"

class ThreadManager {
public:
	ThreadManager(const std::string hashedPassword, const int nbThread);
	~ThreadManager();
	void compute_average_time_sha256();
	
private:
	Utils utils;
	WordGenerator generator;
	
	std::deque<std::thread> producers;
	std::deque<std::thread> consumers;
	std::chrono::time_point<std::chrono::system_clock> start;
	std::chrono::time_point<std::chrono::system_clock> end;
};

#endif /* ThreadManager_hpp */
