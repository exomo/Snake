#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Field.h"

namespace ExomoSnake
{

    enum class Direction
    {
        Right,
        Left,
        Up,
        Down
    };

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

        /* Initialisiere die Schlange mit vorgegebener Position, Richtung und L�nge */
        void initialize(int x, int y, Direction dir, int length = 1);

        /* �ndere die Bewegungsrichtung der Schlange */
        void setDirection(Direction direction);

        Direction getCurrentDirection() const;

        /* Bewege die Schlange um ein Feld in die aktuelle Bewegungsrichtung */
        MoveResult moveStep(Field& field);

        /* Lasse die Schlange im n�chsten Schritt ein Teil l�nger werden */
        void addBodyPart();

        /* Pr�fe ob die Schlange sich aktuell auf einem bestimmten Feld befindet */
        bool isOnTile(const Tile& tile);
    protected:
    private:
        /* Eigenschaften */
        Direction direction;     // Richtung in die sich die Schlange als n�chstes bewegen soll
        Direction lastDirection; // Richtung in die sich die Schlange beim letzten Schritt bewegt hat

        BodyPart head;
        std::vector<BodyPart> body;

        int bodyPartsToAdd;
    };

}

#endif // SNAKE_H
