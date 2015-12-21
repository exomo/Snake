#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <vector>
#include <string>

namespace ExomoSnake
{
    // Jeder Eintrag in der Highscore ist ein Paar aus Punktzahl und Name
    using entry = std::pair<int, std::string>;

    class Highscore
    {
        public:
            /** Default constructor */
            Highscore();
            /** Default destructor */
            virtual ~Highscore();

            /* Lokale Highscore aus Datei laden */
            void loadFromFile();

            /* Lokale Highscore in Datei speichern */
            void saveToFile();

            /* Print to stdout */
            void print();

            /* Add a new Score and return the position if it is in the Highscore */
            int addScore(int score, std::string name);


        protected:
        private:
            std::vector<entry> highscoreList;
    };

}
#endif // HIGHSCORE_H
