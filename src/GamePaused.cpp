#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "GameActive.h"
#include "GameMainMenu.h"
#include "GamePaused.h"

using namespace ExomoSnake;

GamePaused::GamePaused(const std::shared_ptr<GameState>& lastState)
    : lastState(lastState)
{
    /* Schriftart laden, die zum Anzeigen von Texten verwendet wird */
    if(!textFont.loadFromFile("./resources/LinLibertine_R_G.ttf"))
    {
        std::cout << "Schriftart kann nicht geladen werden" << std::endl;
    }
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

    std::wostringstream gamePausedText;
    gamePausedText << L"Spiel angehalten\n\n"
                 << L"Drücke P um fortzufahren\nDrücke <Esc> um zum\nHauptmenü zurückzukehren";

    menuText.setFont(textFont);
    menuText.setString(gamePausedText.str());
    menuText.setCharacterSize(50);
    menuText.setColor(sf::Color::Cyan);
    menuText.setPosition(70, 70);
    window.draw(menuText);
}
