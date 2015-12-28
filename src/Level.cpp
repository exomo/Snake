#include "Level.h"

#include <sstream>

using namespace ExomoSnake;

Level::Level()
    : name(L"Bis zum bitteren Ende")
    , pointsToWin(150)
    , speed(200)
    , startPosition(2,2)
{
    // Default level ist eine Wand an allen Rändern
    for(int x=0; x<sizeX; ++x)
    {
        field[x][0] = '*';
        field[x][sizeY-1] = '*';
    }
    for(int y=0; y<sizeY; ++y)
    {
        field[0][y] = '*';
        field[sizeX-1][y] = '*';
    }
}

int Level::GetPointsToWin() const
{
    return pointsToWin;
}

TileType Level::GetTileType(int x, int y) const
{
    return (field[x][y] == '*') ? TileType::Wall : TileType::Empty;
}

const std::wstring& Level::GetName() const
{
    return name;
}

int Level::GetSpeed() const
{
    return speed;
}

std::pair<int,int> Level::GetStartPosition() const
{
    return startPosition;
}

Direction Level::GetStartDirection() const
{
    return startDirection;
}

void Level::LoadFromFile(const std::string& filename)
{
    std::wifstream file(filename);
    std::wstring line;
    int y = 0;

    // Die erste Zeile ist der Name des Levels
    std::getline(file, name);

    // Die zweite Zeile enthält die Punkte zum Gewinnen und die Geschwindigkeit
    std::getline(file, line);
    std::wistringstream iss(line);
    iss >> pointsToWin >> speed;
    if(pointsToWin < 1 || pointsToWin > 230)
    {
        throw loadlevel_exception(filename, "Ungültige Angabe für Punkte");
    }
    if(speed < 20 || speed > 1000)
    {
        throw loadlevel_exception(filename, "Ungültige Angabe für Geschwindigkeit");
    }

    // Alle anderen Zeilen beschreiben das Spielfeld
    while(std::getline(file, line))
    {
        // Wenn mehr Zeilen in der Datei sind als das Spielfeld hat wird eine exception geworfen
        if(y >= sizeY)
        {
            throw loadlevel_exception(filename, "Zu viele Zeilen");
        }
        // Zeilen müssen genau die richtige Länge haben
        if(line.length() != sizeX)
        {
            throw loadlevel_exception(filename, "Zeile hat eine falsche Länge");
        }

        for(int x = 0; x < sizeX; ++x)
        {
            // Wand wird gespeichert
            switch(line[x])
            {
            case '*':
            case 'X':
            case 'x':
                field[x][y] = '*';
                break;

            case '<':
                field[x][y] = ' ';
                startPosition = std::make_pair(x,y);
                startDirection = Direction::Left;
                break;

            case '>':
                field[x][y] = ' ';
                startPosition = std::make_pair(x,y);
                startDirection = Direction::Right;
                break;

            case '^':
                field[x][y] = ' ';
                startPosition = std::make_pair(x,y);
                startDirection = Direction::Up;
                break;

            case 'v':
                field[x][y] = ' ';
                startPosition = std::make_pair(x,y);
                startDirection = Direction::Down;
                break;

            default:
                field[x][y] = ' ';
                break;

            }
        }

        ++y;
    }
    // Wenn weniger Zeilen in der Datei sind als das Spielfeld hat wird eine exception geworfen
    if(y < sizeY)
    {
        throw loadlevel_exception(filename, "Zu wenige Zeilen");
    }
}
