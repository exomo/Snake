#include "Item.h"

using namespace ExomoSnake;

Item::Item()
{
    //ctor
}

Item::~Item()
{
    //dtor
}

Apple::Apple()
{
    sprite = sf::CircleShape(20, 3);
    sprite.setFillColor(sf::Color::Red);
    sprite.setOrigin(20,20);
}

void Apple::drawTo(sf::RenderTarget& target) const
{
    target.draw(sprite);
}

void Apple::setPosition(const sf::Vector2f& position)
{
    sprite.setPosition(position);
}
