#ifndef GAMEACTIVE_H
#define GAMEACTIVE_H

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Snake.h"
#include "Field.h"

namespace ExomoSnake
{
    /*
     * Zustand in dem das Spiel l�uft. Hier l�uft das eigentliche Spiel.
     */
    class GameActive : public GameState
    {
    public:
        /** Default constructor */
        GameActive();
        /** Default destructor */
        virtual ~GameActive();

        void handleEvent(const sf::Event& event) override;
        GameStatePtr updateGame(sf::Time elapsed, const std::shared_ptr<GameState>& currentState) override;
        void render(sf::RenderWindow& window) override;
    protected:
    private:
        /* Teilkomponenten, das Spielfeld und die Schlange. */
        Field field;
        Snake snake;

        /* Zeitpunkt (vergangene Zeit seit Spielstart), an dem die Schlange das letzte mal einen Schritt bewegt wurde. */
        sf::Time lastMoveTime = sf::Time::Zero;

        /* Aktuelle Geschwindigkeit des Spiels. Zeit in ms bis die Schlange bewegt wird. */
        int speedLevel = 500;

        /* Resourcen f�r Grafik und Text */
        sf::Font textFont;

        bool pauseRequested = false;
        bool paused = true;

        int score = 0;
    };

}


#endif // GAMEACTIVE_H
