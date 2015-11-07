#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <memory>
#include <SFML/Graphics.hpp>

namespace ExomoSnake
{

    /*
     * Abstrakte Basisklasse für den Spielzustand. In jedem Spielzustand müssen werden die drei Methoden
     * handleEvents(), updateGame() und render() implementiert werden. Spielzustände sind z.B. "das Spiel läuft"
     * oder "Im Menü".
     */
    class GameState
    {
    public:
        /** Default constructor */
        GameState();
        /** Default destructor */
        virtual ~GameState();

        virtual void handleEvent(const sf::Event& event) = 0;
        virtual std::shared_ptr<GameState> updateGame(sf::Time elapsed, const std::shared_ptr<GameState>& currentState) = 0;
        virtual void render(sf::RenderWindow& window) = 0;
    };
    using GameStatePtr = std::shared_ptr<GameState>;

    class StateMachine
    {
    public:
        StateMachine(const GameStatePtr& initialState);

    protected:
        GameStatePtr currentState;
    };

}

#endif // GAMESTATE_H
