#ifndef GAMEMAINMENU_H
#define GAMEMAINMENU_H

#include "GameState.h"

namespace ExomoSnake
{

    class GameMainMenu : public GameState
    {
    public:
        /** Default constructor */
        GameMainMenu();
        /** Default destructor */
        virtual ~GameMainMenu();

        void handleEvent(const sf::Event& event) override;
        GameStatePtr updateGame(sf::Time elapsed, const std::shared_ptr<GameState>& currentState) override;
        void render(sf::RenderWindow& window) override;
    protected:
    private:
        /* Resourcen f�r Grafik und Text */
        sf::Font textFont;

        bool exitRequested = false;
        bool startRequested = false;
    };

}
#endif // GAMEMAINMENU_H
