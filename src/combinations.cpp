//
//  combinations.cpp
//  sha256BruteForce
//
//  Created by Thomas Fouan on 01/10/2017.
//  Copyright © 2017 Thomas Fouan. All rights reserved.
//

#include "combinations.hpp"

WordGenerator::WordGenerator(const std::string hashedPassword): queue(), mutex(), cv() {
	this->hashedPassword = hashedPassword;
}
	
void WordGenerator::generateWords(const unsigned int startLength, const unsigned int endLength) {
	
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

bool WordGenerator::testWords() {
	
	std::cout << "Test words. hashed password : " << hashedPassword << std::endl;
	
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
		}
	} while (!passwordFound);
	
	{
		std::unique_lock<std::mutex> lock(mutex);
		assert(queue.size() == 0);
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
