//
//  combinations.hpp
//  sha256BruteForce
//
//  Created by Thomas Fouan on 01/10/2017.
//  Copyright © 2017 Thomas Fouan. All rights reserved.
//

#ifndef combinations_hpp
#define combinations_hpp

#include <stdio.h>
#include <iomanip>
#include <queue>
#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <openssl/sha.h>

const std::string MIN_LETTERS = "abcdefghijklmnopqrstuvwxyz";
const std::string MAJ_LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string NUMBERS = "0123456789";
const std::string CHARSET = MIN_LETTERS + MAJ_LETTERS + NUMBERS + " ";

class WordGenerator {
public:
	WordGenerator(const std::string hashedPassword);
	~WordGenerator();
	void generateWords(const unsigned int startLength, const unsigned int endLength);
	bool testWords();
	static std::string sha256(const std::string str);
	
private:
	std::queue<std::string> queue;
	std::mutex mutex;
	std::condition_variable cv;
	std::string hashedPassword;
	
	const char* CHARSET_POINTERS = CHARSET.c_str();
	uint8_t nbFinishedProducers = 0;
	uint8_t nbProducers = 0;
	bool passwordFound = false;
	uint64_t nbTestedWords = 0;
};

#endif /* combinations_hpp */
