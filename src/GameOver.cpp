#include "GameState.h"
#include "GameActive.h"
#include "GameMainMenu.h"
#include "GameOver.h"

#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>

using namespace ExomoSnake;

GameOver::GameOver(int score)
    : score(score)
    , textFont(GlobalResources::GetInstance().GetFont())
{
    /* Lade Highscore-Liste */
    highscore.loadFromFile(highscoreFile);

    if(highscore.getPosition(score) > -1)
    {
        // newHighscore = true;
        enterName = true;
    }
}

GameOver::~GameOver()
{
    //dtor
}

void GameOver::handleEvent(const sf::Event& event)
{
    if(enterName)
    {
        switch(event.type)
        {
        case sf::Event::TextEntered:
            if(event.text.unicode == 8)
            {
                if(!enteredName.empty())
                {
                    enteredName.resize(enteredName.length()-1);
                }
            }
            else if(event.text.unicode == 13)
            {
                highscorePosition = highscore.addScore(score, enteredName);
                highscore.saveToFile(highscoreFile);
                enterName = false;
            }
            else if(event.text.unicode == 27)
            {
                exitRequested = true;
            }
            else
            {
                enteredName += event.text.unicode;
            }
            break;
        }
    }
    else
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
}

GameStatePtr GameOver::updateGame(sf::Time elapsed, const std::shared_ptr<GameState>& currentState)
{
    if(startRequested)
    {
        return std::make_shared<GameActive>();
    }
    if(exitRequested)
    {
        return std::make_shared<GameMainMenu>();
    }
    if(enterName)
    {

        if((elapsed - lastCursorChanged).asMilliseconds() >= cursorBlinkTime)
        {
            cursorOn = !cursorOn;
            lastCursorChanged = elapsed;
        }
    }
    return nullptr;
}

void GameOver::printEnterName(sf::RenderWindow& window)
{
    sf::Text menuText;

    std::wostringstream enterNameText;
    enterNameText << L"Neue Bestleistung\n"
                  << L"Gib deinen Namen ein: \n"
                  << enteredName;

    if(cursorOn)
    {
         enterNameText << L"|";
    }

    menuText.setFont(textFont);
    menuText.setString(enterNameText.str());
    menuText.setCharacterSize(50);
    menuText.setColor(sf::Color::Blue);
    menuText.setPosition(50, 150);
    window.draw(menuText);
}

void GameOver::printHighscoreList(sf::RenderWindow& window)
{
    sf::Text menuText;

    std::wostringstream highscoreText;
    highscoreText << L"Highscores\n";

    menuText.setFont(textFont);
    menuText.setString(highscoreText.str());
    menuText.setCharacterSize(50);
    menuText.setColor(sf::Color::Blue);
    menuText.setPosition(50, 150);
    window.draw(menuText);

    highscore.drawTo(window, 70, 205, highscorePosition);
}

void GameOver::render(sf::RenderWindow& window)
{
    window.clear(sf::Color(125,50,0, 255));

    sf::Text menuText;

    std::wostringstream gameOverText;
    gameOverText << L"Spiel vorbei\n"
                 << L"Deine Punktzahl: " << score << "\n";

    menuText.setFont(textFont);
    menuText.setString(gameOverText.str());
    menuText.setCharacterSize(50);
    menuText.setColor(sf::Color::Blue);
    menuText.setPosition(50, 20);
    window.draw(menuText);

    if(enterName)
    {
        printEnterName(window);
    }
    else
    {
        printHighscoreList(window);
        menuText.setString(L"<Enter> Neues Spiel - <Esc> Hauptmenü");
        menuText.setPosition(50, 520);
        menuText.setCharacterSize(40);
        window.draw(menuText);
    }
}
