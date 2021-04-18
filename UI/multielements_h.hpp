#define SFML_STATIC

#ifndef UI_MULTIELEMENTS_H_HPP
#define UI_MULTIELEMENTS_H_HPP

#include <SFML/Graphics.hpp>
#include <elements.hpp>
#include "concrete.hpp"
#include "methods.hpp"
#include <iostream>
#include <string>

namespace UI {
    template<class BackgroundType> class MultiElementGhost;
    template<class BackgroundType> class Table;

    template<class BackgroundType = sf::RectangleShape> class MultiElement : public Element<BackgroundType> {
    protected:
        sf::Vector2u gridSpace;
        sf::Vector2f padding;
        Table* table;
        std::vector<MultiElementGhost<BackgroundType>*> ghosts;
    public:
        MultiElement(
            sf::Font& font,
            std::string str = "",
            const sf::Vector2u& initSpace = {1u, 1u},
            const sf::Vector2f& pad = {4.f, 4.f},
            unsigned int charSize = 16,
            const sf::Vector2f& initSize = {-1.f, -1.f},
            const sf::Vector2f& pos = {0.f, 0.f},
            const sf::Color& textColor = sBlack,
            const sf::Color& bgColor = sWhite
        );
        void setGridSpace(const sf::Vector2u& newSpace = {1u, 1u});
        void setPadding(const sf::Vector2f& pad = {4.f, 4.f});
        void setSize(const sf::Vector2f& size = {0.f, 0.f});
        void addGhost(MultiElementGhost<BackgroundType>* ghost);
        void setTable(Table<BackgroundType>* newTable);
        sf::Vector2u getGridSpace() const;
        sf::Vector2f getPadding() const;
        const sf::Font& getFont() const;
    };


    template<class BackgroundType = sf::RectangleShape> class MultiElementGhost : public MultiElement<BackgroundType> {
    protected:
        MultiElement<BackgroundType>* ghosted;
    public:
        MultiElementGhost(MultiElement<BackgroundType>* ghost);
        void setGridSpace(const sf::Vector2u& newSpace = {1u, 1u});
    };
};

#endif