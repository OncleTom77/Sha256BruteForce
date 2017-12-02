//
//  main.cpp
//  sha256BruteForce
//
//  Created by Thomas Fouan on 24/09/2017.
//  Copyright © 2017 Thomas Fouan. All rights reserved.
//

#include <iomanip>
#include <sstream>
#include <queue>
#include <thread>

#include "combinations.hpp"
#include "ThreadManager.hpp"
#include "avxImpl.hpp"

using namespace std;

// Le nombre de chaines de caractères de taille N possibles pour un ensemble C de caractères (minuscules, majuscules, chiffres, etc) est égal à C^N.
//
// Pour les lettres minuscules et :
// 		- des chaines de caractères de taille 2 : 676
// 		- des chaines de caractères de taille 3 : 17 576
// 		- des chaines de caractères de taille 4 : 456 976
// 		- des chaines de caractères de taille 8 : 208 827 064 576
//
// Pour les chiffres et :
// 		- des chaines de caractères de taille 2 : 100
// 		- des chaines de caractères de taille 3 : 1 000
// 		- des chaines de caractères de taille 4 : 10 000
// 		- des chaines de caractères de taille 8 : 100 000 000
//
// Pour les lettres minuscules, majuscules, les chiffres et :
// 		- des chaines de caractères de taille 2 : 3 844
// 		- des chaines de caractères de taille 3 : 238 328
// 		- des chaines de caractères de taille 4 : 14 776 336
// 		- des chaines de caractères de taille 8 : 218 340 105 584 896
//  	- des chaines de caractères de taille 16 : 4,767240170682353e28

int main(int argc, const char * argv[]) {
	int nbConcurrentThreadsSupported = thread::hardware_concurrency();
	const string hashedPassword = WordGenerator::sha256("    ");
	
	cout << "Number of concurrent threads supported : " << nbConcurrentThreadsSupported << endl;
	cout << "Charset : " << CHARSET << endl;
	cout << "Hash : " << hashedPassword << endl;

	ThreadManager threadManager(hashedPassword, 1);
	
//	threadManager.compute_average_time_sha256();

	return 0;
}

