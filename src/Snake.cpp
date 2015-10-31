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
    : head(20, sf::Color(200, 50,50))
{
}

Snake::~Snake()
{
    //dtor
}

void Snake::initialize(int x, int y, Direction dir, int length)
{
    direction = dir;
    head.setPosition(FieldPosition(x,y));
    body.clear();
    bodyPartsToAdd = length;
}

void Snake::setDirection(Direction direction)
{
    this->direction = direction;
}

MoveResult Snake::moveStep(Field& field)
{
    /* Hier wird tats�chlich die Schlange bewegt. Je nach aktueller Bewegungsrichtung wird
     * die x oder y Koordinate des Schlangenkopfs um eins erh�ht oder verringert. */
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

    /* Falls die Schlange noch verl�ngert werden muss, weil sie vorher einen Apfel gefressen hat,
     * wird ein neues K�rperteil erzeugt und hinten angeh�ngt. Pro Bewegungsschritt wird nur ein
     * neues Teil eingef�gt */
    if(bodyPartsToAdd > 0)
    {
        int partRadius = 20;
        BodyPart bodyPart(partRadius, sf::Color(100,250,50));
        body.push_back(bodyPart);
        --bodyPartsToAdd;
    }
    else
    {
        const auto& lastPartPosition = body.back().getPosition();
        field.getTile(lastPartPosition).unblock();
    }

    /* Der K�rper wird nachgezogen. Jedes K�rperteil nimmt die Position des vorausgehenden Teils ein. */
    for(int i=body.size()-1; i>0; --i)
    {
        body[i].setPosition(body[i-1].getPosition());
    }
    body[0].setPosition(head.getPosition());
    /* Die neue Position des Schlangenkopfs setzen */
    head.setPosition(headPosition);


    /* Nachdem die Schlange bewegt wurde wird gepr�ft, ob dadurch eine Kollision entsteht.
     * Dazu wird als erstes das aktuelle Feld des Spielfelds geholt. */
    auto& nextTile = field.getTile(headPosition);

    /* Pr�fen ob die Schlange eine Wand trifft */
    if(nextTile.isWall())
    {
        return MoveResult::HitWall;
    }

    /* Pr�fen ob die Schlange sich selbst frisst */
    for(const auto& bodyPart : body)
    {
        if(bodyPart.getPosition() == head.getPosition())
        {
            return MoveResult::HitWall;
        }
    }

    /* Das Feld als blockiert markieren. Das wird ben�tigt um neue Items
     * nicht an Stellen zu erzeugen wo die Schlange gerade ist. */
     nextTile.block();

    /* Pr�fe ob die Schlange ein Objekt (z.B. Apfel) gefunden hat */
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
    /* Zeichne die K�rperteile */
    for(const auto& bodyPart : body)
    {
        target.draw(bodyPart.getShape());
    }
    /* Zeichne den Kopf */
    target.draw(head.getShape());
}

bool Snake::isOnTile(const Tile& tile)
{
    /* Gehe durch alle K�rperteile und pr�fe ob sich eines auf dem
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
