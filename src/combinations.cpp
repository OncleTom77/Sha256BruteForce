//
//  combinations.cpp
//  sha256BruteForce
//
//  Created by Thomas Fouan on 01/10/2017.
//  Copyright © 2017 Thomas Fouan. All rights reserved.
//

#include "combinations.hpp"

WordGenerator::WordGenerator(const std::string hashedPassword): queue(), mutex(), cv(), hashedPassword(hashedPassword) {
}

WordGenerator::~WordGenerator() {
	queue = {};
}

void WordGenerator::generateWords(const unsigned int startLength, const unsigned int endLength) {
	
	{
		std::lock_guard<std::mutex> lock(mutex);
		++nbProducers;
	}
	
	for (unsigned short length = startLength; length < endLength && !passwordFound; length++) {
		char** pointers = (char**) malloc(length * sizeof(char*));
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
			
			{
				std::lock_guard<std::mutex> lock(mutex);
				stop = passwordFound;
				queue.push(str);
				cv.notify_one();
//				std::cout << str << std::endl;
			}
			
			// Incrémente l'index du premier pointeur pouvant être incrémenté et remet à zéro les précédents qui ne peuvaient pas l'être
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
		
		{
			std::lock_guard<std::mutex> lock(mutex);
			std::cout << "Length done : " << length << std::endl;
			std::cout << "Queue size : " << queue.size() << std::endl;
		}
		
		free(pointers);
	}
	
	{
		std::lock_guard<std::mutex> lock(mutex);
		++nbFinishedProducers;
		cv.notify_all();
		std::cout << "Producer finished. Found = " << passwordFound << std::endl;
	}
	
	return;
}

void WordGenerator::generateWordsChar(const char startChar, const char endChar) {
	
	{
		std::lock_guard<std::mutex> lock(mutex);
		++nbProducers;
	}
	
	for (unsigned short length = 1; length < 6 && !passwordFound; length++) {
		char** pointers = (char**) malloc(length * sizeof(char*));
		bool stop = false;
		
		for (int i = 0; i < length; i++) {
			pointers[i] = (char*) CHARSET_POINTERS;
		}
		
		// On commences à générer des mots qu'à partir de startChar
		pointers[0] += startChar;
		
		do {
			// Récupère le mot à partir du tableau d'index
			std::string str = "";
			for (int i = 0; i < length; i++) {
				str += (char) *pointers[i];
			}
			
			{
				std::lock_guard<std::mutex> lock(mutex);
				stop = passwordFound;
				queue.push(str);
				cv.notify_one();
//				std::cout << str << std::endl;
			}
			
			// Incrémente l'index du premier pointeur pouvant être incrémenté et remet à zéro les précédents qui ne peuvaient pas l'être
			for (int i = length - 1; i >= 0; i--) {
				if (i == 0 && pointers[i] - CHARSET_POINTERS == endChar) {
					stop = true;
				} else if (pointers[i] - CHARSET_POINTERS < CHARSET.length() - 1) {
					pointers[i]++;
					break;
				} else {
					pointers[i] = (char*) CHARSET_POINTERS;
				}
			}
		} while(!stop && length > 0);
		
		{
			std::lock_guard<std::mutex> lock(mutex);
			std::cout << "Length done : " << length << std::endl;
			std::cout << "Queue size : " << queue.size() << std::endl;
		}
		
		free(pointers);
	}
	
	{
		std::lock_guard<std::mutex> lock(mutex);
		++nbFinishedProducers;
		cv.notify_all();
		std::cout << "Producer finished. Found = " << passwordFound << std::endl;
	}
	
	return;
}

void WordGenerator::generateAndTestWords(const char startChar, const char endChar) {
	
	for (unsigned short length = 1; length < 6 && !passwordFound; length++) {
		char** pointers = (char**) malloc(length * sizeof(char*));
		bool stop = false;
		
		for (int i = 0; i < length; i++) {
			pointers[i] = (char*) CHARSET_POINTERS;
		}
		
		// On commences à générer des mots qu'à partir de startChar
		pointers[0] += startChar;
		
		do {
			// Récupère le mot à partir du tableau d'index
			std::string str = "";
			for (int i = 0; i < length; i++) {
				str += (char) *pointers[i];
			}
			
			std::string resultedHash = sha256(str);
			
			if (resultedHash == hashedPassword) {
				std::lock_guard<std::mutex> lock(mutex);
				std::cout << "'" << str << "' is the password !" << std::endl;
				passwordFound = true;
			}
			
			// Incrémente l'index du premier pointeur pouvant être incrémenté et remet à zéro les précédents qui ne peuvaient pas l'être
			for (int i = length - 1; i >= 0; i--) {
				if (i == 0 && pointers[i] - CHARSET_POINTERS == endChar) {
					stop = true;
				} else if (pointers[i] - CHARSET_POINTERS < CHARSET.length() - 1) {
					pointers[i]++;
					break;
				} else {
					pointers[i] = (char*) CHARSET_POINTERS;
				}
			}
		} while(!stop && length > 0 && !passwordFound);
		
		{
			std::lock_guard<std::mutex> lock(mutex);
			std::cout << "Length done : " << length << ". From " << (char) *(CHARSET_POINTERS + startChar) << " to " << (char) *(CHARSET_POINTERS + endChar) << std::endl;
		}
		
		free(pointers);
	}
	
	{
		std::lock_guard<std::mutex> lock(mutex);
		std::cout << "Thread finished. Found = " << passwordFound << std::endl;
	}
	
	return;
}

bool WordGenerator::testWords() {
	do {
		{
			std::unique_lock<std::mutex> lock(mutex);
			cv.wait(lock, [&] {
				return !queue.empty() || nbFinishedProducers == nbProducers;
			});
			
			if(nbFinishedProducers == nbProducers) {
				break;
			}
			
			assert(nbFinishedProducers < nbProducers);
			assert(queue.size() > 0);
			
			// Hash le mot
			std::string str = queue.front();
			std::string resultedHash = sha256(str);
			
			if (resultedHash == hashedPassword) {
				std::cout << "'" << str << "' is the password !" << std::endl;
				passwordFound = true;
			}
			queue.pop();
			++nbTestedWords;
			
			if (nbTestedWords % 1000000 == 0) {
				std::cout << nbTestedWords << " tested words" << std::endl;
				std::cout << "Current tested word : '" << str << "'" << std::endl;
				std::cout << "Queue size : " << queue.size() << std::endl;
			}
		}
	} while (!passwordFound);
	
	{
		std::unique_lock<std::mutex> lock(mutex);
		std::cout << "Consumer finished. Found = " << passwordFound << std::endl;
	}
	
	return passwordFound;
}
	
std::string WordGenerator::sha256(const std::string str) {
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
