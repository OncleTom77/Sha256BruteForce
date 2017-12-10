#ifndef WordGenerator_hpp
#define WordGenerator_hpp

#include <stdio.h>
#include <iomanip>
#include <queue>
#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <mutex>
#include "HeaderFiles/sha.h"

const std::string MIN_LETTERS = "abcdefghijklmnopqrstuvwxyz";
const std::string MAJ_LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string NUMBERS = "0123456789";
const std::string CHARSET = MIN_LETTERS + MAJ_LETTERS + NUMBERS + " ";
const unsigned short MAX_PASSWORD_LENGTH = 100;

class WordGenerator {
public:
	WordGenerator(const std::string hashedPassword);
	~WordGenerator();
	
	/**
	 * Génère les mots commençant par les caractères 'startChar' à 'endChar'.
	 * Exemple : si startChar = 'a', endChar = 'd', génère les mots a.., b.., c.., d..
	 */
	void generateAndTestWords(const char startChar, const char endChar);
	
private:
	std::queue<std::string> queue;
	std::mutex mutex;
	std::string hashedPassword;
	
	const char* CHARSET_POINTERS = CHARSET.c_str();
	bool passwordFound = false;
};

#endif /* WordGenerator_hpp */
