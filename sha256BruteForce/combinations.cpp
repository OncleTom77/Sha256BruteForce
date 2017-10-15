//
//  combinations.cpp
//  sha256BruteForce
//
//  Created by Thomas Fouan on 01/10/2017.
//  Copyright © 2017 Thomas Fouan. All rights reserved.
//

#include "combinations.hpp"

const char* CHARSET_POINTERS = CHARSET.c_str();

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

bool get_all_combinations_iteratif(int length, std::string passwordHash) {
	char** pointers = (char**) malloc(sizeof(char*) * length);
	bool stop = false;
	
	for (int i = 0; i < length; i++) {
		pointers[i] = (char*) CHARSET_POINTERS;
	}
	
	do {
		// Récupère le mot à partir du tableau d'index
		std::string str = "";
		for (int j = 0; j < length; j++) {
			str += (char) *pointers[j];
		}
//		std::cout << str << std::endl;
		
		// Hash le mot
		std::string resultedHash = sha256(str);
		if (resultedHash == passwordHash) {
			std::cout << "'" << str << "' is the password !" << std::endl;
			free(pointers);
			return true;
		}
		
		// Incrémente l'index du premier pointeur pouvant être incrémenté et remet à zéro les précédents qui ne peuvent pas être incrémenté
		for (int i = length - 1; i >= 0; i--) {
			if (pointers[i] - CHARSET_POINTERS < CHARSET.length() - 1) {
				pointers[i]++;
				break;
			} else if(i == 0) {
				stop = true;
			} else {
				pointers[i] = (char*) CHARSET_POINTERS;
			}
		}
	} while(!stop && length > 0);
	
	free(pointers);
	return false;
}

std::string sha256(const std::string str) {
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str.c_str(), str.size());
	SHA256_Final(hash, &sha256);
	std::stringstream ss;
	
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		ss << std::hex << std::setw(2) << std::setfill('0') << (int) hash[i];
	}
	
	return ss.str();
}
