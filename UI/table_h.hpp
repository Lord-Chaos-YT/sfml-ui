#define SFML_STATIC

#ifndef UI_TABLE_H_HPP
#define UI_TABLE_H_HPP

#include <SFML/Graphics.hpp>
#include <multielements_h.hpp>
#include "concrete.hpp"
#include "methods.hpp"
#include <iostream>
#include <string>

namespace UI {
    template<class BackgroundType = sf::RectangleShape> class Table : public Concrete {
    private:
        BackgroundType background;
        std::vector<std::vector<MultiElement<BackgroundType>>> elements;
        sf::Vector2f innerPadding, outerPadding, calcedElementSize;
        sf::Vector2u calcedGridSize;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            target.draw(background, states);
            for (std::vector<MultiElement<BackgroundType>>& column : elements) for (MultiElement<BackgroundType>& elem : column) target.draw(elem, states);
        }

        void recomputePos();
        void recomputeSizes();
    public:
        Table(const std::vector<std::vector<MultiElement<BackgroundType>>>& initElems = {}, const sf::Vector2f& size = {0.f, 0.f}, const sf::Vector2f& innerPad = {4.f, 4.f}, const sf::Vector2f& outerPad = {4.f, 4.f});

        void setPosition(const sf::Vector2f& pos);
        void setSize(const sf::Vector2f& size);
        void setAllElements(const std::vector<std::vector<MultiElement<BackgroundType>>>& elems);
        void insert(const MultiElement<BackgroundType>& inserted, const sf::Vector2u& place, bool lockY = false);
        void erase(const sf::Vector2u& place);
        void replaceElement(const MultiElement<BackgroundType>& replaced, sf::Vector2u place = {-1u, -1u});

        const std::vector<const std::vector<const MultiElement<BackgroundType>>>& getElements() const;
        sf::Vector2f getPosition() const;
        sf::Vector2f getSize() const;
        sf::Vector2u getTableSize() const;
    };
};

#endif