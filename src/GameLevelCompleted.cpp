#include "GameState.h"
#include "GameActive.h"
#include "GameMainMenu.h"
#include "GameLevelCompleted.h"
#include "GlobalResources.h"

#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>


using namespace ExomoSnake;

GameLevelCompleted::GameLevelCompleted(const std::shared_ptr<GameState>& lastState)
    : lastState(lastState)
    , textFont(GlobalResources::GetInstance().GetFont())
{
}

GameLevelCompleted::~GameLevelCompleted()
{
    //dtor
}

void GameLevelCompleted::handleEvent(const sf::Event& event)
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
            resumeRequested = true;
        }
        break;

    default:
        break;
    }
}

GameStatePtr GameLevelCompleted::updateGame(sf::Time elapsed, const std::shared_ptr<GameState>& currentState)
{
    if(resumeRequested)
    {
        return lastState;
    }
    if(exitRequested)
    {
        lastState.reset();
        return std::make_shared<GameMainMenu>();
    }
    return nullptr;
}

void GameLevelCompleted::render(sf::RenderWindow& window)
{
    lastState->render(window);

    sf::Text menuText;

    menuText.setFont(textFont);
    menuText.setColor(sf::Color::Cyan);
    menuText.setString(L"Level beendet");
    menuText.setCharacterSize(50);
    menuText.setPosition(70, 70);
    window.draw(menuText);

    menuText.setString(L"<Enter> Nächstes Level\n<Esc> Hauptmenü");
    menuText.setCharacterSize(40);
    menuText.setPosition(80, 130);
    window.draw(menuText);
}
