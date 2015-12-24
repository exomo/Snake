#include "Highscore.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace ExomoSnake;

namespace
{
    struct CompareHighscore
    {
        bool operator() (const std::pair<const int, std::wstring>& a, const std::pair<const int, std::wstring>& b)
        {
            return a.first > b.first;
        }
    };

    const std::wstring trim( const std::wstring& s)
    {
        auto first = s.find_first_not_of(' ');
        if( first == std::wstring::npos) {
            return std::wstring();
        }
        else {
            auto last = s.find_last_not_of(' ');
            return s.substr( first, last - first + 1);
        }
    }
}

Highscore::Highscore()
    : resources(GlobalResources::GetInstance())
{
    //ctor
}

Highscore::~Highscore()
{
    //dtor
}

/* Lokale Highscore aus Datei laden */
void Highscore::loadFromFile(std::string filename)
{
    std::wifstream fileIn(filename);
    std::wstring line;
    std::wistringstream iss;
    int score;
    std::wstring name;
    while(std::getline(fileIn, line))
    {
        iss.clear();
        iss.str(line);
        iss >> score;
        getline(iss, name);
        addScore(score, trim(name));
    }
}

/* Lokale Highscore in Datei speichern */
void Highscore::saveToFile(std::string filename)
{
    std::wofstream fileOut(filename);
    for(const auto& entry : highscoreList)
    {
        fileOut << entry.first << L" " << entry.second << L"\n";
    }
    fileOut.close();
}

void Highscore::print()
{
    for(const auto& score : highscoreList)
    {
        std::wcout << std::setw(5) << std::setfill(L' ') << score.first << L"  " << score.second << L"\n";
    }
}

int Highscore::addScore(int score, const std::wstring& name)
{
    // Der Neue Eintrag wird in die Highscore-Liste einsortiert
    auto iter = std::upper_bound(highscoreList.begin(), highscoreList.end(), std::make_pair(score, name), CompareHighscore());
    int position = iter - highscoreList.begin();
    highscoreList.insert(iter, std::make_pair(score, trim(name)));


    // Wenn mehr als das Maximum an Einträgen in der List e sind wird der Letzte gelöscht.
    if(highscoreList.size() > MAX_ENTRIES)
    {
        highscoreList.resize(MAX_ENTRIES);
    }

    if(position < MAX_ENTRIES)
    {
        return position;
    }
    else
    {
        return -1;
    }
}

int Highscore::getPosition(int score)
{
    auto iter = std::upper_bound(highscoreList.begin(), highscoreList.end(), std::make_pair(score, L""), CompareHighscore());
    int position = iter - highscoreList.begin();
    if(position < MAX_ENTRIES)
    {
        return position;
    }
    else
    {
        return -1;
    }
}

const std::vector<entry>& Highscore::getList()
{
    return highscoreList;
}

void Highscore::drawTo(sf::RenderTarget& target, int x, int y, int highlightPosition)
{
    const int placeX = x;
    const int nameX  = x + 50;
    const int scoreX = x + 500;
    sf::Text menuText;

    std::wostringstream highscoreText;
    menuText.setFont(resources.GetFont());
    menuText.setCharacterSize(30);

    for(int i = 0; i < highscoreList.size(); ++i)
    {
        // Textfarbe ist rot wenn der Platz gerade neu eingetreagen wurde.
        if(i == highlightPosition)
        {
            menuText.setColor(sf::Color::Red);
        }
        else
        {
            menuText.setColor(sf::Color::Blue);
        }

        // Y Position for den aktuellen Eintrag festlegen
        auto currentY = y + (30 * i);

        // Platznummer schreiben, linksbündig
        menuText.setPosition(placeX, currentY);
        highscoreText.str(L"");
        highscoreText << (i+1) << L". ";
        menuText.setString(highscoreText.str());
        menuText.setOrigin(0, 0);
        target.draw(menuText);

        // Name schreiben, linksbündig
        menuText.setPosition(nameX, currentY);
        menuText.setString(highscoreList[i].second);
        menuText.setOrigin(0, 0);
        target.draw(menuText);

        // Punktzahl schreiben, rechtsbündig
        menuText.setPosition(scoreX, currentY);
        highscoreText.str(L"");
        highscoreText << highscoreList[i].first;
        menuText.setString(highscoreText.str());
        auto rect = menuText.getLocalBounds();
        menuText.setOrigin(rect.width, 0);
        target.draw(menuText);
    }
}
