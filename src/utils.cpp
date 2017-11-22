//
//  utils.cpp
//  sha256BruteForce
//
//  Created by Thomas Fouan on 14/10/2017.
//  Copyright © 2017 Thomas Fouan. All rights reserved.
//

#include "utils.hpp"

void Utils::print_queue(std::queue<std::string> *my_queue) {
	std::cout << "Size : " << std::to_string(my_queue->size()) << std::endl;
	
	while (!my_queue->empty()) {
		std::cout << my_queue->front() << std::endl;
		my_queue->pop();
	}
	*my_queue = {};
}

void Utils::print_stats(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end) {
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	
	std::cout << "finished computation at " << ctime(&end_time)
	<< "elapsed time: " << elapsed_seconds.count() << "s" << std::endl
	<< std::endl;
}

void Utils::print_stats_thread(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end, unsigned short length) {
	
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "Time to test all strings of " << length << " characters : " << elapsed_seconds.count() << "s" << std::endl;
}
