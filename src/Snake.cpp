#include "Snake.h"

using namespace ExomoSnake;


BodyPart::BodyPart(int radius, sf::Color color)
    : shape(radius)
{
    shape.setFillColor(color);
}

const sf::Shape& BodyPart::getShape() const
{
    return shape;
}
const FieldPosition& BodyPart::getPosition() const
{
    return position;
}

void BodyPart::setPosition(const FieldPosition& newPosition)
{
    position = newPosition;
    shape.setPosition(40 * position.first + 20, 40 * position.second + 20);
    shape.setOrigin(20, 20);
}

Snake::Snake()
    : head(20, sf::Color(200, 50, 50))
{
}

Snake::~Snake()
{
    //dtor
}

void Snake::initialize(int x, int y, Direction dir, int length)
{
    direction = dir;
    lastDirection = dir;
    head.setPosition(FieldPosition(x,y));
    body.clear();
    bodyPartsToAdd = length;
}

void Snake::setDirection(Direction direction)
{
    this->direction = direction;
}

Direction Snake::getCurrentDirection() const
{
    return lastDirection;
}

MoveResult Snake::moveStep(Field& field)
{
    /* Hier wird tatsächlich die Schlange bewegt. Je nach aktueller Bewegungsrichtung wird
     * die x oder y Koordinate des Schlangenkopfs um eins erhöht oder verringert. */
    FieldPosition headPosition = head.getPosition();
    switch(direction)
    {
    case Direction::Right:
        ++headPosition.first;
        break;

        case Direction::Left:
        --headPosition.first;
        break;

        case Direction::Down:
        ++headPosition.second;
        break;

        case Direction::Up:
        --headPosition.second;
        break;
    }
    lastDirection = direction;

    /* Falls die Schlange noch verlängert werden muss, weil sie vorher einen Apfel gefressen hat,
     * wird ein neues Körperteil erzeugt und hinten angehängt. Pro Bewegungsschritt wird nur ein
     * neues Teil eingefügt */
    if(bodyPartsToAdd > 0)
    {
        int partRadius = 20;
        BodyPart bodyPart(partRadius, sf::Color(100, 250, 50));
        body.push_back(bodyPart);
        --bodyPartsToAdd;
    }
    else
    {
        const auto& lastPartPosition = body.back().getPosition();
        field.getTile(lastPartPosition).unblock();
    }

    /* Der Körper wird nachgezogen. Jedes Körperteil nimmt die Position des vorausgehenden Teils ein. */
    for(int i=body.size()-1; i>0; --i)
    {
        body[i].setPosition(body[i-1].getPosition());
    }
    body[0].setPosition(head.getPosition());
    /* Die neue Position des Schlangenkopfs setzen */
    head.setPosition(headPosition);


    /* Nachdem die Schlange bewegt wurde wird geprüft, ob dadurch eine Kollision entsteht.
     * Dazu wird als erstes das aktuelle Feld des Spielfelds geholt. */
    auto& nextTile = field.getTile(headPosition);

    /* Prüfen ob die Schlange eine Wand trifft */
    if(nextTile.isWall())
    {
        return MoveResult::HitWall;
    }

    /* Prüfen ob die Schlange sich selbst frisst */
    for(const auto& bodyPart : body)
    {
        if(bodyPart.getPosition() == head.getPosition())
        {
            return MoveResult::HitWall;
        }
    }

    /* Das Feld als blockiert markieren. Das wird benötigt um neue Items
     * nicht an Stellen zu erzeugen wo die Schlange gerade ist. */
     nextTile.block();

    /* Prüfe ob die Schlange ein Objekt (z.B. Apfel) gefunden hat */
    if(nextTile.hasItem())
    {
        auto itemPtr = nextTile.getItem();
        addBodyPart();
        return MoveResult::FoundFruit;
    }
    return MoveResult::Ok;
}

void Snake::addBodyPart()
{
    ++bodyPartsToAdd;
}

void Snake::drawTo(sf::RenderTarget& target)
{
    /* Zeichne die Körperteile */
    for(const auto& bodyPart : body)
    {
        target.draw(bodyPart.getShape());
    }
    /* Zeichne den Kopf */
    target.draw(head.getShape());
}

bool Snake::isOnTile(const Tile& tile)
{
    /* Gehe durch alle Körperteile und prüfe ob sich eines auf dem
     * angegebenen Feld befindet */
    if(head.getPosition() == tile.getPosition())
    {
        return true;
    }
    for(const auto& bodyPart : body)
    {
        if(bodyPart.getPosition() == tile.getPosition())
        {
            return true;
        }
    }
    return false;
}
