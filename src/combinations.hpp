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
#include <openssl/sha.h>

const std::string MIN_LETTERS = "abcdefghijklmnopqrstuvwxyz";
const std::string MAJ_LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string NUMBERS = "0123456789";
const std::string CHARSET = MIN_LETTERS + MAJ_LETTERS + NUMBERS + " ";

class WordGenerator {
public:
	const char* CHARSET_POINTERS = CHARSET.c_str();
	std::string hashedPassword;
	
	WordGenerator(const std::string hashedPassword);
	bool generateAndTestWords(const unsigned int length);
	static std::string sha256(const std::string str);
};

#endif /* combinations_hpp */
