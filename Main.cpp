#include "SnakeGame.h"
#include "Highscore.h"

#include <iostream>

int main()
{
    try
    {
        ExomoSnake::SnakeGame game;
        game.run();
    }
    catch(std::exception& e)
    {
        /*
        * Alle Exceptions die beim Ausführen des Spiels auftreten werden gefangen. Die Fehlermeldung wird auf der
        * Konsole ausgegeben und dann wird das Programm sauber beendet.
        */
        std::cout << "Fataler Fehler:\n" << e.what() << "\n" << std::endl;
        return 1;
    }

    return 0;
}
