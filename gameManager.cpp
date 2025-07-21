#include "gamemanager.h"

	
	GameManager::GameManager(std::ifstream& file)
	{
		srand((unsigned int)time(NULL));
		gameOver = false;
		count = 0;
		unsigned int lineChoice = rand();
		std::string word = selectWord(file, lineChoice);
		initilizeWord(word);
	}

	unsigned int GameManager::countLines(std::istream& file)
	{
		unsigned int numLines = 0;

		while (std::getline(file, line))
		{
			++numLines;
		}

		file.clear();
		file.seekg(0);

		return numLines;
	}


	void GameManager::initilizeWord(std::string word)
	{
		unsigned int i = 0;

		std::transform(word.begin(), word.end(), word.begin(), tolower);

		for (char c : word)
		{
			guessed.push_back(false);
		}

		for (char c : line)
		{
			if (c != ' ')
			{
				std::cout << '_';
				++totalLength;
			}
			else
			{
				std::cout << ' ';
			}
		}

		std::cout << "\n\n";
	}

	std::string GameManager::selectWord(std::istream& file, unsigned int lineChoice)
	{
		unsigned int lineCounter = 0;

		unsigned int wordChoice = lineChoice % countLines(file);

		while (wordChoice != lineCounter)
		{
			std::getline(file, line);
			++lineCounter;
		}

		return line;
	}

	void GameManager::printLetters()
	{
		unsigned int i = 0;

		for (char c : line)
		{
			if (c != ' ')
			{
				if (guessed[i])
				{
					std::cout << c;
				}
				else
				{
					std::cout << "_";
				}
			}
			else
				std::cout << " ";

			++i;
		}

		std::cout << "\n";
	}

	bool GameManager::checkAnswer(const char guess)
	{
		unsigned int i = 0;
		bool noLetters = true;

		if (guessedLetters.find(guess) != guessedLetters.end())
		{
			std::cout << "You already guessed that letter. Try again!\n\n";
			return false;
		}
		std::cout << "\n";
		for (char c : line)
		{

			if (c == guess)
			{
				guessed[i] = true;
				++count;
				noLetters = false;
			}

			++i;
		}

		guessedLetters.insert(guess);

		if (noLetters)
		{
			if (wrongGuesses > 5)
			{
				gameOver = true;
				std::cout << "Oh no! You didn't get the word. The word was\n\n";
				std::cout << "\n" + line + "\n";
			}
			else
			{
				std::cout << "Nope!\n";
				++wrongGuesses;
			}
		}

		if (count == totalLength)
		{
			gameOver = true;
			std::cout << "\nCongratulations! You won the game!\n";
			std::cout << "\n" + line + "\n";
		}

		return gameOver;
	}

	char GameManager::inputCheckerAndConverter(std::string entry)
	{
		char guess;

		while (entry.length() > 1 || !std::isalpha(entry[0]))
		{
			std::cout << "Please enter a single letter\n";
			std::cin >> entry;
		}
		
		guess = tolower(entry[0]);

		return guess;
	}

	void GameManager::runGame()
	{
		std::cout << "The word has been chosen, please select a letter\n\n";

		std::cin >> entry;

		letterChoice = inputCheckerAndConverter(entry);

		checkAnswer(letterChoice);

		while (!gameOver)
		{
			printLetters();

			std::cout << "\n\nGuess another letter\n\n";

			std::cin >> entry;

			letterChoice = inputCheckerAndConverter(entry);

			checkAnswer(letterChoice);
		}
	}