//
//  combinations.hpp
//  sha256BruteForce
//
//  Created by Thomas Fouan on 01/10/2017.
//  Copyright © 2017 Thomas Fouan. All rights reserved.
//

#ifndef combinations_hpp
#define combinations_hpp

#include <stdio.h>
#include <iomanip>
#include <queue>
#include <iostream>
#include <sstream>
#include <string>
#include <openssl/sha.h>

const std::string MIN_LETTERS = "abcdefghijklmnopqrstuvwxyz";
const std::string MAJ_LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string NUMBERS = "0123456789";
const std::string CHARSET = MIN_LETTERS + MAJ_LETTERS + NUMBERS + " ";

/*
 * Ne fait pas ce que l'on souhaite.
 * Permet d'obtenir toutes les permutations d'une chaine de caractères.
 * Exemple pour "abc" : "abc", "acb", "bac", "bca", "cab", "cba"
 */
void get_all_permutations(std::string prefix, std::string base, std::queue<std::string> *queue);

/*
 * Permet d'obtenir toutes les chaines de caractères possibles de taille 'length' selon un ensemble de caractères.
 * Exemple pour le charset "abc" et une taille de 2 : "aa", "ab", "ac", "ba", "bb", "bc", "ca", "cb", "cc"
 */
void get_all_combinations(std::string charset, std::string str, int length, std::queue<std::string> *queue);

/*
 * Appelle 'test_function' sur toutes les combinaisons possibles de taille 'length' pour un charset définit.
 */
bool test_all_combinations(std::string charset, std::string str, int length, bool (*test_function) (std::string));

/*
 * Génère tous les mots possibles sur la longueur donnée, avec le charset défini plus haut.
 */
bool get_all_combinations_iteratif(int length, const std::string passwordHash);

/**
 * Fonction de hash d'un mot avec l'algorithme sha256.
 */
std::string sha256(const std::string str);

#endif /* combinations_hpp */
