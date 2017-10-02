//
//  combinations.cpp
//  sha256BruteForce
//
//  Created by Thomas Fouan on 01/10/2017.
//  Copyright © 2017 Thomas Fouan. All rights reserved.
//

#include "combinations.hpp"

void get_all_permutations(std::string prefix, std::string base, std::queue<std::string> *my_queue) {
	if (base.empty()) {
//		my_queue->push(prefix);
//		std::cout << prefix << std::endl;
	} else {
		for (int i = 0; i < base.length(); i++) {
			std::string newPrefix = prefix + base[i];
			my_queue->push(newPrefix);
//			std::cout << newPrefix << std::endl;
			get_all_permutations(newPrefix, base.substr(0, i) + base.substr(i + 1), my_queue);
		}
	}
}

void get_all_combinations(std::string charset, std::string str, int length, std::queue<std::string> *my_queue) {
	if (length == 0) {
		// Print or add in a list the current string
		if (my_queue != NULL) {
			my_queue->push(str);
		} else {
			std::cout << str << std::endl;
		}
	} else {
		for (int i = 0; i < charset.length(); i++) {
			get_all_combinations(charset, str + charset[i], length - 1, my_queue);
		}
	}
}

bool test_all_combinations(std::string charset, std::string str, int length, bool (*test_function) (std::string)) {
	if (length == 0) {
		if (test_function(str)) {
			return true;
		}
	} else {
		for (int i = 0; i < charset.length(); i++) {
			if (test_all_combinations(charset, str + charset[i], length - 1, test_function)) {
				return true;
			}
		}
	}
	
	return false;
}
