#include "GameState.h"
#include "GameActive.h"
#include "GameMainMenu.h"
#include "GamePaused.h"
#include "GlobalResources.h"

#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>


using namespace ExomoSnake;

GamePaused::GamePaused(const std::shared_ptr<GameState>& lastState)
    : lastState(lastState)
    , textFont(GlobalResources::GetInstance().GetFont())
{
}

GamePaused::~GamePaused()
{
    //dtor
}

void GamePaused::handleEvent(const sf::Event& event)
{
    switch(event.type)
    {
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::Escape)
        {
            exitRequested = true;
        }

        if(event.key.code == sf::Keyboard::P || event.key.code == sf::Keyboard::Pause)
        {
            resumeRequested = true;
        }
        break;

    default:
        break;
    }
}

GameStatePtr GamePaused::updateGame(sf::Time elapsed, const std::shared_ptr<GameState>& currentState)
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

void GamePaused::render(sf::RenderWindow& window)
{
    lastState->render(window);

    sf::Text menuText;

    menuText.setFont(textFont);
    menuText.setColor(sf::Color::Cyan);
    menuText.setString(L"Spiel angehalten");
    menuText.setCharacterSize(50);
    menuText.setPosition(70, 70);
    window.draw(menuText);

    menuText.setString(L"<P> Spiel fortsetzen\n<Esc> Hauptmenü");
    menuText.setCharacterSize(40);
    menuText.setPosition(80, 130);
    window.draw(menuText);
}
