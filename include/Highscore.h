#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include "GlobalResources.h"

#include <vector>
#include <string>

namespace ExomoSnake
{
    // Jeder Eintrag in der Highscore ist ein Paar aus Punktzahl und Name
    using entry = std::pair<int, std::wstring>;

    class Highscore
    {
    public:
        /** Default constructor */
        Highscore();
        /** Default destructor */
        virtual ~Highscore();

        /* Lokale Highscore aus Datei laden */
        void loadFromFile(std::string filename);

        /* Lokale Highscore in Datei speichern */
        void saveToFile(std::string filename);

        /* Print to stdout */
        void print();

        /* Add a new Score and return the position if it is in the Highscore */
        int addScore(int score, const std::wstring& name);

        int getPosition(int score);

        const std::vector<entry>& getList();

        /* Schreibe die Highscore-Liste auf das Zeichenfenster an der angegebenen Position */
        void drawTo(sf::RenderTarget& target, int x, int y, int highlightPosition);


    protected:
    private:
        std::vector<entry> highscoreList;
        const GlobalResources& resources;
        const int MAX_ENTRIES = 10;
    };

}
#endif // HIGHSCORE_H
