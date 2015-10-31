#ifndef ITEM_H
#define ITEM_H

#include <memory>
#include <SFML/Graphics.hpp>

namespace ExomoSnake
{

    class Item
    {
        public:
            Item();
            virtual ~Item();
            virtual void setPosition(const sf::Vector2f& position) = 0;
            virtual void drawTo(sf::RenderTarget& target) const = 0;

        protected:
        private:

    };

    using ItemPtrU = std::unique_ptr<Item>;

    class Apple : public Item
    {
    public:
        Apple();
        void setPosition(const sf::Vector2f& position) override;
        virtual void drawTo(sf::RenderTarget& target) const override;

    private:
        sf::CircleShape sprite;
    };

}

#endif // ITEM_H
