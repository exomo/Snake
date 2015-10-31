#include "Field.h"
#include "Item.h"

using namespace ExomoSnake;

Tile::Tile(bool isWall, int x, int y)
    : tileType(isWall)
    , position(x,y)
    , sprite(sf::RectangleShape(sf::Vector2f(40,40)))
    , blocked(false)
    , item(nullptr)
{
    /* Mittelpunkt, Position und Farbe des zu zeichnenden Objekts festlegen */
    sprite.setOrigin(20,20);
    sprite.setPosition(40 * x + 20, 40 * y + 20);
    if(tileType)
    {
        sprite.setFillColor(sf::Color::Yellow);
    }
    else
    {
        sprite.setFillColor(sf::Color::Transparent);
    }
}

bool Tile::isWall() const
{
    return tileType;
}

void Tile::drawTo(sf::RenderTarget& target) const
{
    target.draw(sprite);
    if(hasItem())
    {
        item->drawTo(target);
    }
}

bool Tile::hasItem() const
{
    return item != nullptr;
}

void Tile::putItem(ItemPtrU& item)
{
    this->item = std::move(item);
    this->item->setPosition(sprite.getPosition());
}

ItemPtrU Tile::getItem()
{
    auto tmpItem = std::move(item);
    item = nullptr;
    return tmpItem;
}

void Tile::block()
{
    blocked = true;
}

void Tile::unblock()
{
    blocked = false;
}

bool Tile::isBlocked() const
{
    return blocked;
}

const FieldPosition& Tile::getPosition() const
{
    return position;
}

Field::Field()
{
    //ctor
}

Field::~Field()
{
    //dtor
}

void Field::initialize(int sizeX, int sizeY)
{
    tiles.resize(sizeX);
    for(int x=0; x<sizeX; ++x)
    {
        // tiles[x].resize(sizeY);
        for(int y=0; y<sizeY; ++y)
        {
            tiles[x].emplace_back((x == 0 || y == 0 || x == sizeX-1 || y == sizeY-1), x, y);
        }
    }
}

void Field::drawTo(sf::RenderTarget& target) const
{
    for(const auto& tileCols : tiles)
    {
        for(const auto& tile : tileCols)
        {
            tile.drawTo(target);
        }
    }
}

Tile& Field::getTile(int x, int y)
{
    return tiles[x][y];
}

Tile& Field::getTile(const FieldPosition& position)
{
    return getTile(position.first, position.second);
}

void Field::addItem(int x, int y, ItemPtrU item)
{
    tiles[x][y].putItem(item);
}

void Field::addItem(const FieldPosition& position, ItemPtrU item)
{
    addItem(position.first, position.second, std::move(item));
}

/* Füge ein Item an einer zufälligen freien Position auf dem Spielfeld ein. */
void Field::addItemAtRandomPosition(ItemPtrU item)
{
    /* Um eine faire Verteilung über alle Felder zu erhalten und zu vermeiden dass
     * ein ungültige Position gewählt wird, wird zuerst eine "Lostrommel" aller freien
     * Felder erstellt und daraus zufällig eines gezogen. */
    std::vector<FieldPosition> lottery;
    for(const auto& col : tiles)
    {
        // tiles[x].resize(sizeY);
        for(const auto& tile : col)
        {
            if(!(tile.isWall() || tile.hasItem() || tile.isBlocked()))
            {
                lottery.push_back(tile.getPosition());
            }
        }
    }
    /* lostrommel mischen */
    random_shuffle(lottery.begin(), lottery.end());

    /* erstes element aus der lostrummel nehmen */
    const auto& newPosition = lottery.front();

    /* das Item an der gezogenen Position einfügen */
    addItem(newPosition, std::move(item));
}
