#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "Highscore.h"

namespace ExomoSnake
{

    class GameOver : public GameState
    {
    public:
        /** Default constructor */
        GameOver(int score);
        /** Default destructor */
        virtual ~GameOver();

        void handleEvent(const sf::Event& event) override;
        GameStatePtr updateGame(sf::Time elapsed, const std::shared_ptr<GameState>& currentState) override;
        void render(sf::RenderWindow& window) override;

        /* Hilfsfunktionen zum anzeigen von verschiedenen Texten */
        void printEnterName(sf::RenderWindow& window);
        void printHighscoreList(sf::RenderWindow& window);

    protected:
    private:
        /* Resourcen für Grafik und Text */
        const sf::Font& textFont;

        int score;
        bool exitRequested = false;
        bool startRequested = false;
        bool enterName = false;
        Highscore highscore;
        std::wstring enteredName;
        bool cursorOn = true;
        sf::Time lastCursorChanged;
        int highscorePosition = -1;
        const int cursorBlinkTime = 300;
        const std::string highscoreFile = "snakeHighscore.esh";
    };

}
#endif // GAMEOVER_H
