#ifndef GAMEACTIVE_H
#define GAMEACTIVE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameState.h"
#include "Snake.h"
#include "Field.h"
#include "Level.h"
#include "GlobalResources.h"

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
        GameStatePtr updateGame(sf::Time elapsed, const std::shared_ptr<GameState>& currentState) override;
        void render(sf::RenderWindow& window) override;
    protected:
    private:
        void InitializeLevel();

        /* Referenz auf den Resourcen Manager */
        const GlobalResources& globalResources;

        /* Teilkomponenten, das Spielfeld und die Schlange. */
        Field field;
        Snake snake;



        /* Zeitpunkt (vergangene Zeit seit Spielstart), an dem die Schlange das letzte mal einen Schritt bewegt wurde. */
        sf::Time lastMoveTime = sf::Time::Zero;

        /* Aktuelle Geschwindigkeit des Spiels. Zeit in ms bis die Schlange bewegt wird. */
        int speedLevel = 500;

        /* Level nummer und Beschreibung */
        int levelNumber = 0;
        Level currentLevel;

        /* Resourcen für Grafik und Text */
        const sf::Font& textFont;
        sf::Sound backgroundMusic;
        sf::Sound appleSound;

        bool pauseRequested = false;
        bool paused = true;

        bool completedRequested = false;
        bool levelCompleted = false;

        int score = 0;
        int levelScore = 0;
    };

}


#endif // GAMEACTIVE_H
