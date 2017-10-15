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
#include "utils.hpp"
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

void compute_average_time_sha256() {
	chrono::time_point<chrono::system_clock> start, end;
	string test[] = {
		"yBnQ3",
		"uV4CG8g25iENkhbtg58YugvKu",
		"77XCORE3H4Gun1HCFhZbhIFUS2yTgmLZys8PciZvjog1Nl7o1n",
		"csHFqTt6Vg40NG52q7XbwBGzh2DxEwmhuuCa0aGyXMItG5DpXW5Z1KeI2Jxi8DVaqZ9hYLB8h7b",
		"SOTsl54CqaozEXO3GfuM3WD780T2E3I0Kv76hnb2KJ2AVrbMXIzpXxvioCPLsn025GgpDoGRpxwk7g2Eas09HbYrm7632Dc3khU6"
	};
	double total = 0.0;

	for (int i = 0; i < 100; i++) {
		start = chrono::system_clock::now();

		// Appel de fonction à changer pour tester différents algorithmes de sha256
		sha256(test[i%5]);

		end = chrono::system_clock::now();
		chrono::duration<double> elapsed_seconds = end - start;
		total += elapsed_seconds.count();
	}

	cout << "Total computation time to generate 100 sha256 hash : " << total << "s" << endl;
}


//
//int main(int argc, const char * argv[]) {
//	chrono::time_point<chrono::system_clock> start_all, end_all, start, end;
//	bool found = false;
//	int nbConcurrentThreadsSupported = thread::hardware_concurrency();
//	string passwordHash = sha256("azert");
//
//	cout << "Number of concurrent threads supported : " << nbConcurrentThreadsSupported << endl;
//	cout << "Charset : " << CHARSET << endl;
//	cout << "Hash : " << passwordHash << endl;
//
////	Affiche toutes les combinaisons possibles sur 1 lettre, puis 2, puis 3, etc
//	start_all = chrono::system_clock::now();
//	cout << "*************** Beginning ***************" << endl;
//	for (unsigned short i = 0; i <= 5 && !found; i++) {
//		start = chrono::system_clock::now();
//		found = get_all_combinations_iteratif(i, passwordHash);
//		end = chrono::system_clock::now();
//
//		if(!found) {
//			print_stats_thread(start, end, i);
//		}
//	}
//	cout << "****************** End ******************" << endl;
//	end_all = chrono::system_clock::now();
//	print_stats(start_all, end_all);
//
//	return 0;
//}







#include <stdio.h>
#include <string.h>
int main(int argc, const char * argv[])
{
	std::string strMessage = "azert1234567890AZERTYUIOPMLKJHGFDSQWXCVBN1234567890 awxA";
	uint32_t length = (uint32_t) strMessage.length();
	
	std::cout << "0x80 : '" << (char) 0x80 << "'" << std::endl;
	std::cout << "0x00 : '" << (char) 0x00 << "'" << std::endl;
	
	uint8_t message[length];
	for (uint32_t i = 0; i < length; i++) {
		message[i] = strMessage[i];
		cout << message[i];
	}
	cout << endl;
	
	/* empty message with padding */
//	uint8_t message[64];
//	memset(message, 0x00, sizeof(message));
//	message[0] = 0x80;

	/* intial state */
	uint32_t state[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

	sha256_process_x86(state, message, (uint32_t) sizeof(message));

	/* E3B0C44298FC1C14... */
	printf("SHA256 hash of empty message: ");
	printf("%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X...\n",
		   (state[0] >> 24) & 0xFF, (state[0] >> 16) & 0xFF, (state[0] >> 8) & 0xFF, (state[0] >> 0) & 0xFF,
		   (state[1] >> 24) & 0xFF, (state[1] >> 16) & 0xFF, (state[1] >> 8) & 0xFF, (state[1] >> 0) & 0xFF,
		   (state[2] >> 24) & 0xFF, (state[2] >> 16) & 0xFF, (state[2] >> 8) & 0xFF, (state[2] >> 0) & 0xFF,
		   (state[3] >> 24) & 0xFF, (state[3] >> 16) & 0xFF, (state[3] >> 8) & 0xFF, (state[3] >> 0) & 0xFF,
		   (state[4] >> 24) & 0xFF, (state[4] >> 16) & 0xFF, (state[4] >> 8) & 0xFF, (state[4] >> 0) & 0xFF,
		   (state[5] >> 24) & 0xFF, (state[5] >> 16) & 0xFF, (state[5] >> 8) & 0xFF, (state[5] >> 0) & 0xFF,
		   (state[6] >> 24) & 0xFF, (state[6] >> 16) & 0xFF, (state[6] >> 8) & 0xFF, (state[6] >> 0) & 0xFF,
		   (state[7] >> 24) & 0xFF, (state[7] >> 16) & 0xFF, (state[7] >> 8) & 0xFF, (state[7] >> 0) & 0xFF);
	
	std::stringstream ss;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		ss << std::hex << std::setw(2) << std::setfill('0') << (int) ((state[i/4] >> (24 - 8*(i%4))) & 0xFF);
	}
	
	cout << ss.str() << endl;
	printf("test : %02X\n", (state[0] >> 28) & 0xFF);
	printf("test : %01X\n", (state[0] >> 24) & 0xFF);

	int success = (((state[0] >> 24) & 0xFF) == 0xE3) && (((state[0] >> 16) & 0xFF) == 0xB0) &&
	(((state[0] >> 8) & 0xFF) == 0xC4) && (((state[0] >> 0) & 0xFF) == 0x42);

	if (success)
		printf("Success!\n");
	else
		printf("Failure!\n");

	return (success != 0 ? 0 : 1);
}









