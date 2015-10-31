#ifndef GAMEACTIVE_H
#define GAMEACTIVE_H

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Snake.h"
#include "Field.h"

namespace ExomoSnake
{
    /*
     * Zustand in dem das Spiel läuft. Hier läuft das eigentliche Spiel.
     */
    class GameActive : public GameState
    {
    public:
        /** Default constructor */
        GameActive();
        /** Default destructor */
        virtual ~GameActive();

        void handleEvent(const sf::Event& event) override;
        GameStatePtr updateGame(sf::Time elapsed) override;
        void render(sf::RenderWindow& window) override;
    protected:
    private:
        /* Teilkomponenten, das Spielfeld und die Schlange. */
        Field field;
        Snake snake;

        /* Zeit die vergangen ist, seit die Schlange das letzte mal einen Schritt bewegt wurde. */
        int elapsedSinceMove = 0;

        /* Aktuelle Geschwindigkeit des Spiels. Zeit in ms bis die Schlange bewegt wird. */
        int speedLevel = 500;

        /* Resourcen für Grafik und Text */
        sf::Font textFont;

        bool pauseRequested = false;

        int score = 0;
    };

}


#endif // GAMEACTIVE_H
