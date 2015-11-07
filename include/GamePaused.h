#ifndef GAMEPAUSED_H
#define GAMEPAUSED_H

#include "GameState.h"

namespace ExomoSnake
{

    class GamePaused : public GameState
    {
        public:
            /** Default constructor */
            GamePaused(const std::shared_ptr<GameState>& lastState);
            /** Default destructor */
            virtual ~GamePaused();

            void handleEvent(const sf::Event& event) override;
            GameStatePtr updateGame(sf::Time elapsed, const std::shared_ptr<GameState>& currentState) override;
            void render(sf::RenderWindow& window) override;

        protected:

        private:
            /* Resourcen für Grafik und Text */
            sf::Font textFont;

            /* Hier wird der letzte aktive Zustand gespeichert, um dort hin zurückkehren zu können */
            std::shared_ptr<GameState> lastState;

            bool exitRequested = false;
            bool resumeRequested = false;
    };

}
#endif // GAMEPAUSED_H
