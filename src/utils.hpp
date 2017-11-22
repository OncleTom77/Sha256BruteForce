//
//  utils.hpp
//  sha256BruteForce
//
//  Created by Thomas Fouan on 14/10/2017.
//  Copyright © 2017 Thomas Fouan. All rights reserved.
//

#ifndef utils_hpp
#define utils_hpp

#include <stdio.h>
#include <queue>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <chrono>

class Utils {
public:
	void print_queue(std::queue<std::string> *my_queue);
	void print_stats(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end);
	void print_stats_thread(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end, unsigned short length);
};

#endif /* utils_hpp */
