#ifndef GAMELEVELCOMPLETED_H
#define GAMELEVELCOMPLETED_H

#include "GameState.h"

namespace ExomoSnake
{

    class GameLevelCompleted : public GameState
    {
        public:
            /** Default constructor */
            GameLevelCompleted(const std::shared_ptr<GameState>& lastState);
            /** Default destructor */
            virtual ~GameLevelCompleted();

            void handleEvent(const sf::Event& event) override;
            GameStatePtr updateGame(sf::Time elapsed, const std::shared_ptr<GameState>& currentState) override;
            void render(sf::RenderWindow& window) override;

        protected:

        private:
            /* Resourcen für Grafik und Text */
            const sf::Font& textFont;

            /* Hier wird der letzte aktive Zustand gespeichert, um dort hin zurückkehren zu können */
            std::shared_ptr<GameState> lastState;

            bool exitRequested = false;
            bool resumeRequested = false;
    };

}

#endif // GAMELEVELCOMPLETED_H
