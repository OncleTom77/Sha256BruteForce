//
//  ThreadManager.cpp
//  sha256BruteForce
//
//  Created by Thomas Fouan on 15/10/2017.
//  Copyright © 2017 Thomas Fouan. All rights reserved.
//

#include "ThreadManager.hpp"

ThreadManager::ThreadManager(const std::string hashedPassword, const int nbThread) : utils(), generator(hashedPassword) {
	
	std::chrono::time_point<std::chrono::system_clock> start_all, end_all, start, end;
	bool found = false;
	
	//	Affiche toutes les combinaisons possibles sur 1 lettre, puis 2, puis 3, etc
	std::cout << "*************** Beginning ***************" << std::endl;
	start_all = std::chrono::system_clock::now();
	
	for (unsigned short i = 0; i <= 5 && !found; i++) {
		start = std::chrono::system_clock::now();
		found = generator.generateAndTestWords(i);
		end = std::chrono::system_clock::now();
		
		if(!found) {
			utils.print_stats_thread(start, end, i);
		}
	}
	
	end_all = std::chrono::system_clock::now();
	std::cout << "****************** End ******************" << std::endl;
	utils.print_stats(start_all, end_all);
}

void ThreadManager::compute_average_time_sha256() {
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::string test[] = {
		"yBnQ3",
		"uV4CG8g25iENkhbtg58YugvKu",
		"77XCORE3H4Gun1HCFhZbhIFUS2yTgmLZys8PciZvjog1Nl7o1n",
		"csHFqTt6Vg40NG52q7XbwBGzh2DxEwmhuuCa0aGyXMItG5DpXW5Z1KeI2Jxi8DVaqZ9hYLB8h7b",
		"SOTsl54CqaozEXO3GfuM3WD780T2E3I0Kv76hnb2KJ2AVrbMXIzpXxvioCPLsn025GgpDoGRpxwk7g2Eas09HbYrm7632Dc3khU6"
	};
	double total = 0.0;
	const unsigned int nbHash = 100000;
	
	std::cout << "Start generation of " << nbHash << " hashs" << std::endl;
	
	for (unsigned int i = 0; i < nbHash; i++) {
		start = std::chrono::system_clock::now();
		
		// Appel de fonction à changer pour tester différents algorithmes de sha256
		generator.sha256(test[i%5]);
		
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		total += elapsed_seconds.count();
	}
	
	std::cout << "Total computation time to generate " << nbHash << " sha256 hash : " << total << "s" << std::endl;
}
