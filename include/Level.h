#ifndef LEVEL_H
#define LEVEL_H

#include "CommonTypes.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>

namespace ExomoSnake
{

    /* Exception-Klasse für Fehler beim Laden der Ressourcen */
    class loadlevel_exception : public std::runtime_error
    {
    public:
        loadlevel_exception(std::string resourcePath, std::string reason)
            : std::runtime_error("Could not load level: " + resourcePath + " - " + reason)
        {
        }

    private:
        std::string resourcePath;
    };

    enum class TileType
    {
        Empty = 0,
        Wall,
    };
    class Level
    {
    public:
        Level();

        int GetPointsToWin() const;
        TileType GetTileType(int x, int y) const;
        const std::wstring& GetName() const;
        int GetSpeed() const;
        std::pair<int,int> GetStartPosition() const;
        Direction GetStartDirection() const;

        void LoadFromFile(const std::string& filename);

    private:
        const static int sizeX = 20;
        const static int sizeY = 15;

        char field[sizeX][sizeY];

        std::wstring name;
        int pointsToWin = 2;
        int speed;
        std::pair<int,int> startPosition;
        Direction startDirection;

    };

}

#endif // LEVEL_H
