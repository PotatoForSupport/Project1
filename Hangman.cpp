#include "GameManager.h"

int main()
{
    const std::string fileName = "wordbank.txt";
    std::ifstream inputFile;

    unsigned short wrongGuesses = 0;
    bool victory = false;

    inputFile.open(fileName);

    GameManager game(inputFile);

    inputFile.close();

    game.runGame();
}
