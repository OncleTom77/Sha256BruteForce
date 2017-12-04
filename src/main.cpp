#include <iomanip>
#include <sstream>
#include <queue>
#include <thread>

#include "WordGenerator.hpp"
#include "ThreadManager.hpp"

/**
 * Converti la chaine de caractères pointé par 'str' en nombre.
 * Retourne -1 si 'str' n'est pas un nombre
 */
long convertToDigit(const char* str) {
	char* ptr;
	long value = strtol(str, &ptr, 10);
	
	return (*ptr) ? -1 : value;
}

/**
 * Point d'entrée du programme. Doit être fourni en ligne de commandes :
 * - le nombre de threads lancé par le programme
 * - le mot de passe hashé par l'algorithme SHA256
 */
int main(int argc, const char * argv[]) {
	if (argc < 3) {
		std::cout << "Veuillez renseigner tous les paramètres (nombre de threads et mot de passe hashé). Exemple d'utilisation : ./main 4 abc..."
		<< std::endl;
		return 0;
	}
	
	const int nbConcurrentThreadsSupported = std::thread::hardware_concurrency();
	long nbThreads = convertToDigit(argv[1]);
	const std::string hashedPassword(argv[2]);
	
	if (nbThreads < 1) {
		std::cout << "Veuillez saisir un nombre de thread supérieur ou égal à 1" << std::endl;
		return 0;
	}
	
	std::cout 	<< "Number of hardware concurrent threads supported : " << nbConcurrentThreadsSupported
				<< ". Number of threads to start : " << nbThreads << std::endl;
	std::cout << "Charset : " << CHARSET << std::endl;
	std::cout << "Hash : " << hashedPassword << std::endl;

	ThreadManager threadManager(hashedPassword, (int) nbThreads);

	return 0;
}
