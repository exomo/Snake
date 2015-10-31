#ifndef FIELD_H
#define FIELD_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Item.h"

namespace ExomoSnake
{
    /* Stellt die Koordinaten auf dem Spielfeld dar. (X, Y) */
    using FieldPosition = std::pair<int,int>;

    class Tile
    {
        public:
            Tile(bool isWall, int x, int y);
            bool isWall() const;
            void drawTo(sf::RenderTarget& target) const;
            bool hasItem() const;
            void putItem(ItemPtrU& item);
            ItemPtrU getItem();
            bool isBlocked() const;
            void block();
            void unblock();
            const FieldPosition& getPosition() const;

        private:
            bool tileType;
            FieldPosition position;
            sf::RectangleShape sprite;
            bool blocked;
            ItemPtrU item;
    };

    class Field
    {
        public:
            Field();
            virtual ~Field();

            Tile& getTile(int x, int y);
            Tile& getTile(const FieldPosition& position);

            void addItem(int x, int y, ItemPtrU item);
            void addItem(const FieldPosition& position, ItemPtrU item);
            void addItemAtRandomPosition(ItemPtrU item);

            void initialize(int sizeX, int sizeY);
            void drawTo(sf::RenderTarget& target) const;

        protected:
        private:
            /* Einzelne Felder des Spielfelds.
             * Die erste Dimension sind Spalten (index = X Werte).
             * In der zweiten Dimension sind die Felder der einzelnen Reihen (index = Y Werte) */
            std::vector<std::vector<Tile>> tiles;
    };

}

#endif // FIELD_H
