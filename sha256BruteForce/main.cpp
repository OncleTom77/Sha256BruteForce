//
//  main.cpp
//  sha256BruteForce
//
//  Created by Thomas Fouan on 24/09/2017.
//  Copyright © 2017 Thomas Fouan. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <sstream>
#include <queue>
#include <openssl/sha.h>
#include "combinations.hpp"
#include <thread>

using namespace std;

const string MIN_LETTERS = "abcdefghijklmnopqrstuvwxyz";
const string MAJ_LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string NUMBERS = "0123456789";

string passwordHash;

bool sha256_test_function(string str);

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

string sha256(const string str) {
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str.c_str(), str.size());
	SHA256_Final(hash, &sha256);
	stringstream ss;
	
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		ss << hex << setw(2) << setfill('0') << (int) hash[i];
	}
	
	return ss.str();
}

/*
 * Hashes the string and compares it with the input hash
 */
bool sha256_test_function(string str) {
	string resultedHash = sha256(str);
	if (resultedHash == passwordHash) {
		std::cout << "'" << str << "' is the password !" << std::endl;
		return true;
	}
	return false;
}

void print_queue(queue<string> *my_queue) {
	cout << "Size : " << to_string(my_queue->size()) << endl;
	/*
	while (!queue->empty()) {
		cout << queue->front() << endl;
		queue->pop();
	}*/
	*my_queue = {};
}

void print_stats(chrono::time_point<chrono::system_clock> start, chrono::time_point<chrono::system_clock> end) {
	chrono::duration<double> elapsed_seconds = end - start;
	time_t end_time = chrono::system_clock::to_time_t(end);
	
	cout << "finished computation at " << ctime(&end_time)
			<< "elapsed time: " << elapsed_seconds.count() << "s" << endl
			<< endl;
}

void print_stats_thread(chrono::time_point<chrono::system_clock> start, chrono::time_point<chrono::system_clock> end, unsigned short length) {
	chrono::duration<double> elapsed_seconds = end - start;
	cout << "Time to test all strings of " << length << " characters : " << elapsed_seconds.count() << "s" << endl;
}

bool task(unsigned short length) {
	chrono::time_point<chrono::system_clock> start, end;
	bool found = false;
	
	start = chrono::system_clock::now();
	found = test_all_combinations(MIN_LETTERS, "", length, &sha256_test_function);
	end = chrono::system_clock::now();
	
	if (!found) {
		print_stats_thread(start, end, length);
	}
	
	return found;
}

void compute_average_time_sha256() {
	chrono::time_point<chrono::system_clock> start, end;
	string test[] = {
		"yBnQ3",
		"uV4CG8g25iENkhbtg58YugvKu",
		"77XCORE3H4Gun1HCFhZbhIFUS2yTgmLZys8PciZvjog1Nl7o1n",
		"csHFqTt6Vg40NG52q7XbwBGzh2DxEwmhuuCa0aGyXMItG5DpXW5Z1KeI2Jxi8DVaqZ9hYLB8h7b",
		"SOTsl54CqaozEXO3GfuM3WD780T2E3I0Kv76hnb2KJ2AVrbMXIzpXxvioCPLsn025GgpDoGRpxwk7g2Eas09HbYrm7632Dc3khU6"
	};
	double average = 0.0;
	
	for(string str : test) {
		start = chrono::system_clock::now();
		sha256(str);
		end = chrono::system_clock::now();
		chrono::duration<double> elapsed_seconds = end - start;
		average += elapsed_seconds.count();
	}
	average /= 5;
	//cout << average * 14000000 << "s" << endl;
	cout << "Average computation time to generate sha256 hash : " << average << "s" << endl;
}

int main(int argc, const char * argv[]) {
	string charset = "abc";
	queue<string> combi_queue = queue<string>();
	chrono::time_point<chrono::system_clock> start, end;
	chrono::time_point<chrono::system_clock> start_all, end_all;
	bool found = false;
	int nbConcurrentThreadsSupported = thread::hardware_concurrency();
	
	cout << "Number of concurrent threads supported : " << nbConcurrentThreadsSupported << endl;
	
//	thread thread1 = thread(&cout, 1);
	
	//compute_average_time_sha256();
	
//	Calcul le temps que prend la fonction de hash
	start = chrono::system_clock::now();
	passwordHash = sha256("test");
	end = chrono::system_clock::now();
	
	cout << "Hash : " << passwordHash << endl;
	print_stats(start, end);
	
//	Affiche toutes les combinaisons possibles sur 1 lettre, puis 2, puis 3, etc
	start_all = chrono::system_clock::now();
	cout << "*************** Beginning ***************" << endl;
	for (unsigned short i = 1; i <= 5 && !found; i++) {
		found = task(i);
	}
	cout << "****************** End ******************" << endl;
	end_all = chrono::system_clock::now();
	print_stats(start_all, end_all);
	
//	get_all_combinations(charset, "", 3, &combi_queue);
//	print_queue(&combi_queue);
//
//	cout << "-------------------------------" << endl;
//	get_all_permutations("", charset, &combi_queue);
//	print_queue(&combi_queue);
	
	return 0;
}
