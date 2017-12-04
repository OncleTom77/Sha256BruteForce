#ifndef utils_hpp
#define utils_hpp

#include <stdio.h>
#include <queue>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <chrono>

class Utils {
public:
	/**
	 * Affiche la date et l'heure à laquelle la fonction a été appelée et affiche le temps écoulé entre la période 'start' et 'end'.
	 */
	void print_stats(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end);
};

#endif /* utils_hpp */
