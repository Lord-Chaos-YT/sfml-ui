#define SFML_STATIC

#ifndef UI_MULTIELEMENTS_HPP
#define UI_MULTIELEMENTS_HPP

#include <SFML/Graphics.hpp>
#include <multielements_h.hpp>
#include "concrete.hpp"
#include "methods.hpp"
#include <iostream>
#include <string>

namespace UI {
    template<class BackgroundType> MultiElement<BackgroundType>::MultiElement(
        sf::Font& font,
        std::string str,
        const sf::Vector2u& initSpace,
        const sf::Vector2f& pad,
        unsigned int charSize,
        const sf::Vector2f& initSize,
        const sf::Vector2f& pos,
        const sf::Color& textColor,
        const sf::Color& bgColor
    ) : Element<BackgroundType>{font, str, charSize, initSize, pos, textColor, bgColor}, gridSpace{initSpace}, padding{pad} {/*Cricket noises*/}

    template<class BackgroundType> void MultiElement<BackgroundType>::setGridSpace(const sf::Vector2u& newSpace) {
        if (!newSpace.x || !newSpace.y) throw "Must use nonzero values for MultiElement grid size.\n";
        gridSpace = newSpace;
        for (MultiElementGhost<BackgroundType>* ghost : ghosts) ghost->setGridSpace({1u, newSpace.y});
    }

    template<class BackgroundType> void MultiElement<BackgroundType>::setPadding(const sf::Vector2f& pad) {padding = pad;}

    template<class BackgroundType> void MultiElement<BackgroundType>::setSize(const sf::Vector2f& size) {
        this->Element<BackgroundType>::setSize({(size.x * (float)gridSpace.x) + (padding.x * (float)(gridSpace.x - 1u)), (size.y * (float)gridSpace.y) + (padding.y * (float)(gridSpace.y - 1u))});
    }

    template<class BackgroundType> void MultiElement<BackgroundType>::addGhost(MultiElementGhost<BackgroundType>* ghost) {
        ghosts.push_back(ghost);
    }

    template<class BackgroundType> void MultiElement<BackgroundType>::setTable(Table<BackgroundType>* newTable) {table = newTable;}

    template<class BackgroundType> sf::Vector2u MultiElement<BackgroundType>::getGridSpace() const {return gridSpace;}
    template<class BackgroundType> sf::Vector2f MultiElement<BackgroundType>::getPadding() const {return padding;}

    template<class BackgroundType> const sf::Font& MultiElement<BackgroundType>::getFont() const {return text.getFont();}
    

    template<class BackgroundType> MultiElementGhost<BackgroundType>::MultiElementGhost(MultiElement<BackgroundType>* ghost) : MultiElement<BackgroundType>{ghost->getFont()}, ghosted{ghost} {
        ghost->addGhost(this);
    }

    template<class BackgroundType> void MultiElementGhost<BackgroundType>::setGridSpace(const sf::Vector2u& newSpace) {
        this->MultiElement<BackgroundType>::setGridSpace({1u, newSpace.y});
    }
};

#endif