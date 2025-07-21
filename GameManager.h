#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <time.h>
#include <random>
#include <utility>
#include <vector>
#include <unordered_set>
#include <cctype>

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

class GameManager
{
	private:

		std::string entry;
		char letterChoice;
		unsigned int totalLength;
		unsigned short wrongGuesses;
		bool gameOver;
		std::string line;
		std::vector<bool> guessed;
		std::unordered_set<char> guessedLetters;
		unsigned int count;

		unsigned int countLines(std::istream& file);

		void initilizeWord(std::string word);

		std::string selectWord(std::istream& file, unsigned int lineChoice);

		void printLetters();

		char inputCheckerAndConverter(std::string entry);

	public:

		GameManager(std::ifstream& file);

		bool checkAnswer(const char guess);

		void runGame();
};
#endif
