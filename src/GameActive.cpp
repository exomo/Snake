﻿#include "GameActive.h"

#include <iostream>
#include <sstream>
#include <string>

#include "GamePaused.h"
#include "GameOver.h"
#include "Item.h"

using namespace ExomoSnake;

GameActive::GameActive()
    : textFont(GlobalResources::GetInstance().GetFont())
    , backgroundMusic(GlobalResources::GetInstance().GetBackgroundMusic())
    , appleSound(GlobalResources::GetInstance().GetAppleSound())
{
    backgroundMusic.setLoop(true);
    backgroundMusic.play();

    field.initialize(20,15);
    field.addItem(10, 10, ItemPtrU(new Apple()) );
    snake.initialize(2, 2, Direction::Right, 2);

    speedLevel = 200;
    pauseRequested = false;
}

GameActive::~GameActive()
{
    //dtor
    backgroundMusic.stop();
}

void GameActive::handleEvent(const sf::Event& event)
{
    /*
     * Die aktuelle Bewegungsrichtung (bei der letzten Bewegung) wird zwischengespeichert.
     * Die aktuelle Richtung wird erst verändert wenn die Schlange sich bewegt hat.
     */
    auto currentDirection = snake.getCurrentDirection();

    switch(event.type)
    {
    case sf::Event::LostFocus:
        /* Hauptfenster hat den Fokus verloren, das Spiel wird pausiert. */
        pauseRequested = true;
        break;

    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::P || event.key.code == sf::Keyboard::Pause)
        {
            /*
             * Hier wird nur gespeichert dass die P Taste gedrückt wurde und in den Pausenbildschirm gewechselt werden soll.
             * Der Zustandswechsel nach "Pause" wird erst im updateGame() Schritt durchgeführt.
             */
            pauseRequested = true;
        }

        /*
         * Wenn 'M' gedrückt wurde wird die Musik ein oder ausgeschaltet
         */
        if(event.key.code == sf::Keyboard::M)
        {
            if(backgroundMusic.getStatus() == sf::Sound::Status::Stopped)
            {
                backgroundMusic.play();
            }
            else
            {
                backgroundMusic.stop();
            }
        }

        /*
         * Richtungstasten ändern die Bewegungsrichtung der Schlange für die nächste Bewegung.
         * Solange bis die Schlange sich tatsächlich bewegt hat kann die
         * Bewegungsrichtung immer wieder überschrieben werden, um eventuelle
         * falsche Eingaben zu korrigieren. Nur Bewegungen die nicht entgegengesetzt zur letzten Bewegung sind
         * sind zugelassen.
         */
        if((event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) && currentDirection != Direction::Right)
            snake.setDirection(Direction::Left);
        if((event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) && currentDirection != Direction::Left)
            snake.setDirection(Direction::Right);
        if((event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) && currentDirection != Direction::Down)
            snake.setDirection(Direction::Up);
        if((event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) && currentDirection != Direction::Up)
            snake.setDirection(Direction::Down);
        break;

    default:
        break;
    }
}

GameStatePtr GameActive::updateGame(sf::Time elapsed, const std::shared_ptr<GameState>& currentState)
{
    /* Wenn die Pause-Taste gedrückt wurde, wird sofort in den Pause-Bildschirm gewechselt,
     * ohne die Schlange zu bewegen. */
    if(pauseRequested)
    {
        /* Die Pausenanforderung wird zurückgesetz, dafür wird gespeichert dass das Spiel gerade pausiert ist. */
        pauseRequested = false;
        paused = true;
        return std::make_shared<GamePaused>(currentState);
    }

    /* Wenn das Spiel pausiert war (hier kommt man erst hin wenn der Pausenmodus verlassen wurde), wird die Zeitmessung
     * bis zur nächsten Bewegung neu gestartet. */
    if(paused)
    {
        paused = false;
        lastMoveTime = elapsed;
    }

    /* Berechne wie lange es her ist seitdem sich die Schlange das letzte Mal einen Schritt bewegt hat.
     * Wenn diese Zeit den aktuellen Geschwindigkeitswert hat, wird die Schlange bewegt. */
    auto elapsedSinceMove = (elapsed - lastMoveTime).asMilliseconds();
    if(elapsedSinceMove >= speedLevel)
    {
        auto moveResult = snake.moveStep(field);
        if(moveResult == MoveResult::FoundFruit)
        {
            /* Wenn die Schlange einen Apfel gefunden hat, wird die Punktzahl erhöht
             * und ein neuer Apfel auf dem Spielfeld platziert. */
            ++score;
            appleSound.play();
            field.addItemAtRandomPosition(ItemPtrU(new Apple()));
        }
        else if(moveResult == MoveResult::HitBody || moveResult == MoveResult::HitWall)
        {
            /* Wenn die Schlange sich selbst oder eine Wand getroffen hat wechselt das
             * Spiel in den Game-Over Bildschirm. */
            return std::make_shared<GameOver>(score);
        }
        /* Der Zähler für die Bewegungszeit wird zurückgesetzt, damit die nächste Bewegung
         * wieder nach der vorgegebenen Zeit berechnet wird. */
        lastMoveTime = elapsed;
    }

    return nullptr;
}

void GameActive::render(sf::RenderWindow& window)
{
    window.clear(sf::Color(25,50,0, 255));

    field.drawTo(window);
    snake.drawTo(window);

    sf::Text scoreText;

    scoreText.setFont(textFont);
    std::wostringstream text;
    text << L"Punkte: " << score;
    scoreText.setString(text.str());
    scoreText.setCharacterSize(24);
    scoreText.setColor(sf::Color::Blue);
    scoreText.setPosition(5, 5);
    window.draw(scoreText);
}
