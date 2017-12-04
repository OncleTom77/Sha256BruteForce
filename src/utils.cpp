#include "utils.hpp"

void Utils::print_stats(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end) {
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	
	std::cout << "computation finished at " << ctime(&end_time)
	<< "elapsed time: " << elapsed_seconds.count() << "s" << std::endl
	<< std::endl;
}
