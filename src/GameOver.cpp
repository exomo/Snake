#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "GameActive.h"
#include "GameMainMenu.h"
#include "GameOver.h"

using namespace ExomoSnake;

GameOver::GameOver(int score)
    : score(score)
{
    /* Schriftart laden, die zum Anzeigen von Texten verwendet wird */
    if(!textFont.loadFromFile("./resources/LinLibertine_R_G.ttf"))
    {
        std::cout << "Schriftart kann nicht geladen werden" << std::endl;
    }
}

GameOver::~GameOver()
{
    //dtor
}

void GameOver::handleEvent(const sf::Event& event)
{
    switch(event.type)
    {
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::Escape)
        {
            exitRequested = true;
        }

        if(event.key.code == sf::Keyboard::Return)
        {
            startRequested = true;
        }
        break;

    default:
        break;
    }
}

GameStatePtr GameOver::updateGame(sf::Time elapsed)
{
    if(startRequested)
    {
        return std::make_shared<GameActive>();
    }
    if(exitRequested)
    {
        return std::make_shared<GameMainMenu>();
    }
    return nullptr;
}

void GameOver::render(sf::RenderWindow& window)
{
    window.clear(sf::Color(125,50,0, 255));

    sf::Text menuText;

    std::ostringstream gameOverText;
    gameOverText << "Spiel vorbei\n"
                 << "Deine Punktzahl: " << score << "\n\n"
                 << "Drücke <Enter> um neu zu starten\nDrücke <Esc> um zum\nHauptmenü zurückzukehren";

    menuText.setFont(textFont);
    menuText.setString(gameOverText.str());
    menuText.setCharacterSize(50);
    menuText.setColor(sf::Color::Blue);
    menuText.setPosition(50, 20);
    window.draw(menuText);

    window.display();
}
