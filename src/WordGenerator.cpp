#include "WordGenerator.hpp"

WordGenerator::WordGenerator(const std::string hashedPassword): queue(), mutex(), hashedPassword(hashedPassword) {
}

WordGenerator::~WordGenerator() {
	queue = {};
}

void WordGenerator::generateAndTestWords(const char startChar, const char endChar) {
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	
	for (unsigned short length = 1; length < MAX_PASSWORD_LENGTH && !passwordFound; length++) {
		char** pointers = (char**) malloc(length * sizeof(char*));
		char* word = (char*) malloc((length + 1) * sizeof(char));
		bool stop = false;
		
		word[length] = '\0';
		
		for (int i = 0; i < length; i++) {
			pointers[i] = (char*) CHARSET_POINTERS;
		}
		
		// On commence à générer des mots qu'à partir de startChar
		pointers[0] += startChar;
		
		do {
			std::stringstream ss;
			std::string resultedHash;
			
			// Récupère le mot à partir du tableau d'index
			for (int i = 0; i < length; i++) {
				word[i] = (char) *pointers[i];
			}
			
			// Hash le mot
			SHA256_Init(&sha256);
			SHA256_Update(&sha256, word, length);
			SHA256_Final(hash, &sha256);
			
			for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
				ss << std::hex << std::setw(2) << std::setfill('0') << (int) hash[i];
			}
			resultedHash = ss.str();
			
			// Compare le hash du mot avec le hash passé en paramètre
			if (resultedHash == hashedPassword) {
				std::lock_guard<std::mutex> lock(mutex);
				std::cout << "'" << std::string(word) << "' is the password !" << std::endl;
				passwordFound = true;
			}
			
			// Incrémente l'index du premier pointeur pouvant être incrémenté et remet à zéro les précédents qui ne peuvaient pas l'être
			for (int i = length - 1; i >= 0; i--) {
				if (i == 0 && pointers[i] - CHARSET_POINTERS == endChar) {
					stop = true;
				} else if (pointers[i] - CHARSET_POINTERS < CHARSET.length() - 1) {
					pointers[i]++;
					break;
				} else {
					pointers[i] = (char*) CHARSET_POINTERS;
				}
			}
		} while(!stop && length > 0 && !passwordFound);
		
		#ifndef NDEBUG
		if (!passwordFound) {
			std::lock_guard<std::mutex> lock(mutex);
			std::cout 	<< "Length done : " << length
						<< ". From " << (char) *(CHARSET_POINTERS + startChar)
						<< " to " << (char) *(CHARSET_POINTERS + endChar) << std::endl;
		}
		#endif
		
		free(word);
		free(pointers);
	}
	
	{
		std::lock_guard<std::mutex> lock(mutex);
		std::cout << "Thread finished. Found = " << (passwordFound ? "YES" : "NO") << std::endl;
	}
	
	return;
}
