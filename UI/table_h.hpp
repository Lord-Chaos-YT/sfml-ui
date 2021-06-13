#ifndef UI_TABLE_H_HPP
#define UI_TABLE_H_HPP

#include <SFML/Graphics.hpp>
#include "elements.hpp"

namespace UI {
    template<class ElementType = sf::RectangleShape, class BackgroundType = sf::RectangleShape> class Table : public sf::Drawable {
    public:
        typedef std::vector<std::vector<ElementType>> ArrayType;
    protected:
        BackgroundType background;
        ArrayType elements;
        sf::Vector2f innerPadding, outerPadding, calcedElementSize;
        sf::Vector2u calcedGridSize;
        bool autoResize = false;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            for (const std::vector<ElementType> column : elements) for (const ElementType element : column) target.draw(element, states);
        }

        void recomputePos();
        void recomputeSizes();
    public:
        Table(const ArrayType& initElems = {}, const sf::Vector2f& size = {0.f, 0.f}, const sf::Vector2f& innerPad = {4.f, 4.f}, const sf::Vector2f& outerPad = {4.f, 4.f});

        void setPosition(const sf::Vector2f& pos);
        void setSize(const sf::Vector2f& size);
        void setAllElements(const ArrayType& elems);
        void insert(const ElementType& inserted, const sf::Vector2i& place = {-1, -1}, bool lockY = false);
        void erase(const sf::Vector2u& place);
        void replaceElement(const ElementType& replaced, sf::Vector2i place = {-1, -1});

        std::vector<std::vector<ElementType&>&>& getElements();
        sf::Vector2f getPosition() const;
        sf::Vector2f getSize() const;
        sf::Vector2u getTableSize() const;
    };
};

#endif