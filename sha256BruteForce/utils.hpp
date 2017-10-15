//
//  utils.hpp
//  sha256BruteForce
//
//  Created by Thomas Fouan on 14/10/2017.
//  Copyright © 2017 Thomas Fouan. All rights reserved.
//

#ifndef utils_hpp
#define utils_hpp

#include <stdio.h>
#include <queue>
#include <sstream>
#include <iomanip>
#include <iostream>

/**
 * Affiche la taille et le contenu d'une Queue.
 */
void print_queue(std::queue<std::string> *my_queue);

/**
 * Affiche le temps qui s'est écoulé entre start et end.
 */
void print_stats(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end);

/**
 * Affiche le temps qui s'est écoulé entre start et end correspondant au temps d'exécution d'un thread. Affiche la taille des caractères qui ont été générés.
 */
void print_stats_thread(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end, unsigned short length);

#endif /* utils_hpp */
