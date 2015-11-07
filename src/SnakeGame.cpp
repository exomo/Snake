#include "SnakeGame.h"
#include "GameActive.h"
#include "GameMainMenu.h"

#include <iostream>

using namespace ExomoSnake;

SnakeGame::SnakeGame()
    : StateMachine(std::make_shared<GameMainMenu>())
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(800, 600), "~~~ Exomo Snake ~~~", sf::Style::Default, settings);
    // window.create(sf::VideoMode::getDesktopMode(), "~~~ Exomo Snake ~~~", sf::Style::Fullscreen);

    /* Für jeden Tastendruck soll nur ein Event erzeugt werden, wenn die Taste gedrückt bleibt werden keine wiederholten "KeyDown" events erzeugt. */
    window.setKeyRepeatEnabled(false);

    /* Verticale Synchronisation aktivieren, verhindert den tearing effekt */
    window.setVerticalSyncEnabled(true);

    /* Das Spiel geht ohne Maus, der Cursor soll im Fenster nicht sichtbar sein */
    window.setMouseCursorVisible(false);
}

SnakeGame::~SnakeGame()
{
}

void SnakeGame::run()
{
    /* Uhr starten. Alle Zeiten werden relativ zu diesem Zeitpunkt angegeben. */
    clock.restart();

    /* Hauptschleife in der das Spiel läuft. */
    while (window.isOpen())
    {
        sf::Time elapsed = clock.getElapsedTime();

        handleEvents();
        updateGame(elapsed);
        render();
    }
}

/* Events verarbeiten. Zum Beispiel Tastatureingaben. */
void SnakeGame::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        /*
         * Die Hauptklasse behandelt "Fenster geschlossen" selbst.
         * Alle anderen Events (vor allem Tastendrücke) werden vom aktuellen Zustand verarbeitet.
         */
        switch(event.type)
        {
        case sf::Event::Closed:
            /* Fenster soll geschlossen werden */
            window.close();
            break;

        default:
            /* Der aktuelle Zustand kann das Event verarbeiten. */
            currentState->handleEvent(event);
            break;
        }
    }
}

/* Spielstatus aktualisieren: Schlange bewegen, kollision berechnen, etc. */
void SnakeGame::updateGame(sf::Time elapsed)
{
    /* Der aktuelle Zustand kann seinen internen Status aktualisieren. */
    auto newState = currentState->updateGame(elapsed, currentState);
    if(newState != nullptr)
    {
        /*
         * Der aktuelle Zustand hat einen Zustandswechsel angefordert.
         * Der neue Zustand ersetzt den alten.
         */
         currentState = newState;
    }
}

void SnakeGame::render()
{
    /* Der aktuelle Zustand zeichnet in das Ausgabefenster. */
    currentState->render(window);
    window.display();
}
