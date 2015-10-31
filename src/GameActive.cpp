#include "GameActive.h"

#include <iostream>
#include <sstream>
#include <string>

#include "GameMainMenu.h"
#include "GameOver.h"
#include "Item.h"

using namespace ExomoSnake;

GameActive::GameActive()
{
    /* Schriftart laden, die zum Anzeigen von Texten verwendet wird */
    if(!textFont.loadFromFile("./resources/LinLibertine_R_G.ttf"))
    {
        std::cout << "Schriftart kann nicht geladen werden" << std::endl;
    }

    field.initialize(20,15);
    field.addItem(10, 10, ItemPtrU(new Apple()) );
    snake.initialize(2, 2, Direction::Right, 2);

    speedLevel = 500;
    elapsedSinceMove = 0;
    pauseRequested = false;
}

GameActive::~GameActive()
{
    //dtor

}

void GameActive::handleEvent(const sf::Event& event)
{
    switch(event.type)
    {
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::Escape)
        {
            /*
             * Hier wird nur gespeichert dass die Escape Taste gedrückt wurde und in den Pausenbildschirm gewechselt werden soll.
             * Der Zustandswechsel nach "Pause" wird erst im updateGame() Schritt durchgeführt.
             */
            pauseRequested = true;
        }
        /*
         * Richtungstasten ändern die Bewegungsrichtung der Schlange.
         * Solange bis die Schlange sich tatsächlich bewegt hat kann die
         * Bewegungsrichtung immer wieder überschrieben werden, um eventuelle
         * falsche Eingaben zu korrigieren.
         */
        if(event.key.code == sf::Keyboard::Left)
            snake.setDirection(Direction::Left);
        if(event.key.code == sf::Keyboard::Right)
            snake.setDirection(Direction::Right);
        if(event.key.code == sf::Keyboard::Up)
            snake.setDirection(Direction::Up);
        if(event.key.code == sf::Keyboard::Down)
            snake.setDirection(Direction::Down);
        break;

    default:
        break;
    }
}

GameStatePtr GameActive::updateGame(sf::Time elapsed)
{
    /* Wenn die Esc-Taste gedrückt wurde, wird sofort in den Startbildschirm gewechselt,
     * ohne die Schlange zu bewegen. */
    if(pauseRequested)
    {
        return std::make_shared<GameMainMenu>();
    }
    /* Berechne wie lange es her ist seitdem sich die Schlange das letzte Mal einen Schritt bewegt hat.
     * Wenn diese Zeit den aktuellen Geschwindigkeitswert hat, wird die Schlange bewegt. */
    elapsedSinceMove += elapsed.asMilliseconds();
    if(elapsedSinceMove >= speedLevel)
    {
        auto moveResult = snake.moveStep(field);
        if(moveResult == MoveResult::FoundFruit)
        {
            /* Wenn die Schlange einen Apfel gefunden hat, wird die Punktzahl erhöht
             * und ein neuer Apfel auf dem Spielfeld platziert. */
            ++score;
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
        elapsedSinceMove = 0;
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
    std::ostringstream text;
    text << "Punkte: " << score;
    scoreText.setString(text.str());
    scoreText.setCharacterSize(24);
    scoreText.setColor(sf::Color::Blue);
    scoreText.setPosition(5, 5);
    window.draw(scoreText);

    window.display();
}
