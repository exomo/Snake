#include "Highscore.h"

#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace ExomoSnake;

Highscore::Highscore()
{
    //ctor
}

Highscore::~Highscore()
{
    //dtor
}

/* Lokale Highscore aus Datei laden */
void Highscore::loadFromFile()
{
    highscoreList.emplace_back(1000, "exomo");
    highscoreList.emplace_back(500, "Adam");
    highscoreList.emplace_back(700, "Barney");
    highscoreList.emplace_back(200, "Caroline");
    highscoreList.emplace_back(123, "Dilbert");
    highscoreList.emplace_back(666, "Ernesto");

    std::sort(highscoreList.begin(), highscoreList.end());
}

/* Lokale Highscore in Datei speichern */
void Highscore::saveToFile()
{

}

void Highscore::print()
{
    for(const auto& score : highscoreList)
    {
        std::cout << std::setw(5) << std::setfill(' ') << score.first << "  " << score.second << "\n";
    }
}

int Highscore::addScore(int score, std::string name)
{
    auto iter = std::upper_bound(highscoreList.begin(), highscoreList.end(), std::make_pair(score, name));
    if(iter != highscoreList.end())
    {
        highscoreList.insert(iter, std::make_pair(score, name));
    }
}
