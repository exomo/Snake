#include "GameMainMenu.h"
#include "GameState.h"
#include "GameActive.h"
#include "GlobalResources.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace ExomoSnake;

GameMainMenu::GameMainMenu()
    : textFont(GlobalResources::GetInstance().GetFont())
{
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
    menuText.setColor(sf::Color::Blue);
    menuText.setString(L"Exomo Snake");
    menuText.setCharacterSize(50);
    menuText.setPosition(50, 20);
    window.draw(menuText);

    menuText.setString(L"<Enter> Spiel starten\n<Esc> Beenden");
    menuText.setCharacterSize(40);
    menuText.setPosition(60, 80);
    window.draw(menuText);
}
