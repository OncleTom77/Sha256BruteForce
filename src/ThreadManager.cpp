#include "ThreadManager.hpp"

ThreadManager::ThreadManager(const std::string hashedPassword, const unsigned nbThread) : threads(), utils(), generator(hashedPassword) {
	
	std::cout << "*************** Beginning ***************" << std::endl;
	start = std::chrono::system_clock::now();
	
	int limit = (int) CHARSET.length() / nbThread;
	
	if (nbThread == 1) {
		threads.emplace_front(std::thread(&WordGenerator::generateAndTestWords, &generator, 0, CHARSET.length() - 1));
	} else if (nbThread > 1) {
		threads.emplace_front(std::thread(&WordGenerator::generateAndTestWords, &generator, 0, limit));
		for (int i = 1; i < nbThread - 1; i++) {
			threads.emplace_front(std::thread(&WordGenerator::generateAndTestWords, &generator, (i * limit) + 1, (i+1) * limit));
		}
		threads.emplace_front(std::thread(&WordGenerator::generateAndTestWords, &generator, ((nbThread - 1) * limit) + 1, CHARSET.length() - 1));
	}
}

ThreadManager::~ThreadManager() {
	for(uint8_t i=0; i<threads.size(); ++i) {
		threads[i].join();
	}
	
	end = std::chrono::system_clock::now();
	std::cout << "****************** End ******************" << std::endl;
	utils.print_stats(start, end);
}
