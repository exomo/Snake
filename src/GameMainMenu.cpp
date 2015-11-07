#include "GameMainMenu.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "GameState.h"
#include "GameActive.h"

using namespace ExomoSnake;

GameMainMenu::GameMainMenu()
{
    /* Schriftart laden, die zum Anzeigen von Texten verwendet wird */
    if(!textFont.loadFromFile("./resources/LinLibertine_R_G.ttf"))
    {
        std::cout << "Schriftart kann nicht geladen werden" << std::endl;
    }
}

GameMainMenu::~GameMainMenu()
{
    //dtor
}

void GameMainMenu::handleEvent(const sf::Event& event)
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

GameStatePtr GameMainMenu::updateGame(sf::Time elapsed, const std::shared_ptr<GameState>& currentState)
{
    if(startRequested)
    {
        return std::make_shared<GameActive>();
    }
    return nullptr;
}

void GameMainMenu::render(sf::RenderWindow& window)
{
    if(exitRequested)
    {
        window.close();
        return;
    }

    window.clear(sf::Color(125,50,0, 255));

    sf::Text menuText;
    menuText.setFont(textFont);
    menuText.setString(L"Exomo Snake\nDrücke <Enter> um zu starten\nDrücke <Esc> um zu beenden");
    menuText.setCharacterSize(50);
    menuText.setColor(sf::Color::Blue);
    menuText.setPosition(50, 20);
    window.draw(menuText);
}
