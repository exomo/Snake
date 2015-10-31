#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <SFML/Graphics.hpp>
#include "GameState.h"

namespace ExomoSnake
{

    /*
     * Hauptklasse. Alles wird innerhalb dieser Klasse ausgeführt.
     * Besitzt das Grafikfenster, liest Tastaturevents und verwaltet den Spielzustand.
     */
    class SnakeGame : public StateMachine
    {
    public:
        SnakeGame();
        ~SnakeGame();

        /* Die Hauptfunktion run() startet das Spiel. */
        void run();

    protected:
    private:
        /*
         * Klassischer Ansatz mit 3 Schritten. Events verarbeiten, Spielzustand aktualisieren, Rendern.
         * Was die 3 Schritte jeweils genau tun hängt vom aktuellen Zustand ab. Jeder Zustand kann seine
         * Logik selbst bestimmen.
         */

        /* 1. Benutzereingaben und evtl. Systemevents verarbeiten. */
        void handleEvents(sf::Time elapsed);

        /* 2. Spielzustand aktualisieren.
           Je nach Eingaben aus Schritt 1 kann das Spiel seinen Zustand ändern.
           Update des Spielzustands nach bestimmter Zeit.
        */
        void updateGame(sf::Time elapsed);

        /* 3. Aktuellen Spielzustand grafisch ausgeben. */
        void render();

        /* Das Fenster in das alles gezeichnet wird */
        sf::RenderWindow window;

        /* Uhr mit der der zeitliche Ablauf gesteuert wird. */
        sf::Clock clock;
    };

}

#endif // SNAKEGAME_H
