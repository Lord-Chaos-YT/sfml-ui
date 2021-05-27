#define SFML_STATIC

#ifndef UI_MULTITABLE_H_HPP
#define UI_MULTITABLE_H_HPP

#include <SFML/Graphics.hpp>
#include <multielements_h.hpp>
#include "concrete.hpp"
#include "methods.hpp"
#include <iostream>
#include <string>

namespace UI {
    template<class BackgroundType = sf::RectangleShape> class Table : public Concrete {
    public:
        typedef MultiElement<BackgroundType> ElementType;
        typedef std::vector<std::vector<ElementType>> ArrayType;
    private:
        BackgroundType background;
        ArrayType elements;
        sf::Vector2f innerPadding, outerPadding, calcedElementSize;
        sf::Vector2u calcedGridSize;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            target.draw(background, states);
            for (std::vector<ElementType>& column : elements) for (ElementType& elem : column) target.draw(elem, states);
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

        const std::vector<const std::vector<const Table<BackgroundType>::ElementType>>& getElements() const;
        sf::Vector2f getPosition() const;
        sf::Vector2f getSize() const;
        sf::Vector2u getTableSize() const;
    };
};

#endif