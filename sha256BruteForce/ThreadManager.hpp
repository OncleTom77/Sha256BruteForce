//
//  ThreadManager.hpp
//  sha256BruteForce
//
//  Created by Thomas Fouan on 15/10/2017.
//  Copyright © 2017 Thomas Fouan. All rights reserved.
//

#ifndef ThreadManager_hpp
#define ThreadManager_hpp

#include <stdio.h>
#include <iomanip>
#include <iostream>

#include "utils.hpp"
#include "combinations.hpp"

class ThreadManager {
public:
	ThreadManager(const std::string hashedPassword, const int nbThread);
	
	void compute_average_time_sha256();
	
private:
	Utils utils;
	WordGenerator generator;
};

#endif /* ThreadManager_hpp */
