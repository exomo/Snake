#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>

#include "Field.h"
#include "CommonTypes.h"

namespace ExomoSnake
{
    enum class MoveResult
    {
        Ok,
        FoundFruit,
        HitWall,
        HitBody
    };

    class BodyPart
    {
    public:
        BodyPart(int radius, sf::Color color);
        const sf::Shape& getShape() const;
        const FieldPosition& getPosition() const;
        void setPosition(const FieldPosition& newPosition);

    private:
        FieldPosition position;
        sf::CircleShape shape;
    };

    class Snake
    {
    public:
        Snake();
        virtual ~Snake();

        /* Zeichne die Schlange auf das Zeichenfenster */
        void drawTo(sf::RenderTarget& target);

        /* Initialisiere die Schlange mit vorgegebener Position, Richtung und Länge */
        void initialize(int x, int y, Direction dir, Field& field, int length = 1);

        /* Ändere die Bewegungsrichtung der Schlange */
        void setDirection(Direction direction);

        Direction getCurrentDirection() const;

        /* Bewege die Schlange um ein Feld in die aktuelle Bewegungsrichtung */
        MoveResult moveStep(Field& field);

        /* Lasse die Schlange im nächsten Schritt ein Teil länger werden */
        void addBodyPart();

        /* Prüfe ob die Schlange sich aktuell auf einem bestimmten Feld befindet */
        bool isOnTile(const Tile& tile);
    protected:
    private:
        /* Eigenschaften */
        Direction direction;     // Richtung in die sich die Schlange sich gerade bewegt
        std::queue<Direction> directionBuffer; // Buffer für die Richtungen in die sich die Schlange als nächstes bewegen soll

        BodyPart head;
        std::vector<BodyPart> body;

        int bodyPartsToAdd;
    };

}

#endif // SNAKE_H
